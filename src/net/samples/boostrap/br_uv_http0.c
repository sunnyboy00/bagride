
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uv.h"
#include "http_parser.h"

#include "br_trace.h"

#define TEST_PORT 6969
#define RD_MAX_CONNECTIONS 64

static int request_num = 0;

#define RESPONSE \
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Content-Length: 12\r\n" \
  "\r\n" \
  "hello world\n"

typedef struct {
    uv_tcp_t handle;
    http_parser parser;
    uv_write_t write_req;
    int request_num;
} cli_t;

static http_parser_settings parser_settings;
static uv_buf_t resbuf;

static void on_close(uv_handle_t* h_) {
    cli_t* cli = (cli_t*) h_->data;
    R_INFO("(%5d) connection closed ", cli->request_num);
    free(cli);
}

static void on_alloc_buffer(uv_handle_t *handle_, size_t suggested_size_, uv_buf_t* buf_) {
    (void) handle_;
    buf_->base = (char*) calloc(suggested_size_, sizeof (char));
    buf_->len = suggested_size_;
}

static void on_after_write(uv_write_t* req_, int status_) {
    R_ASSERT(status_ >= 0);

    uv_close((uv_handle_t*) req_->handle, on_close);
}

static void on_read(uv_stream_t* tcp_, ssize_t nread_, const uv_buf_t* buf_) {
    size_t parsed;
    cli_t* client = (cli_t*) tcp_->data;

    if (nread_ >= 0) {
        parsed = http_parser_execute(
                &client->parser, &parser_settings, buf_->base, (size_t) nread_);

        if (parsed < (size_t) nread_) {
            R_ERR("parse error");
            uv_close((uv_handle_t*) tcp_, on_close);
        }

    } else {
        uv_close((uv_handle_t*) tcp_, on_close);
    }
    free(buf_->base);
}

static void on_connect(uv_stream_t* pserver_, int status_) {
    R_ASSERT(status_ >= 0);
    ++request_num;

    cli_t* cli = calloc(1, sizeof (cli_t));
    cli->request_num = request_num;

    R_INFO("(%5d) connection new %p", cli->request_num, pserver_);

    uv_tcp_init(uv_default_loop(), &cli->handle);
    http_parser_init(&cli->parser, HTTP_REQUEST);

    cli->parser.data = cli;
    cli->handle.data = cli;

    if (uv_accept(pserver_, (uv_stream_t*) & cli->handle) == 0) {
        uv_read_start((uv_stream_t*) & cli->handle, on_alloc_buffer, on_read);
    } else {
        uv_close((uv_handle_t*) & cli->handle, on_close); 
    }
}

static int on_headers_complete(http_parser* parser) {
    cli_t* cli = (cli_t*) parser->data;
    R_INFO("(%5d) http message parsed", cli->request_num);
    uv_write(
            &cli->write_req,
            (uv_stream_t*) & cli->handle,
            &resbuf,
            1,
            on_after_write);
    return 1;
}

int main(int argc, char** argv) {

    (void) argc;
    (void) argv;
    
    parser_settings.on_headers_complete = on_headers_complete;
    resbuf.base = strdup( RESPONSE );
    resbuf.len = sizeof (RESPONSE);

    struct sockaddr_in addr = {0};
    uv_tcp_t server;
    uv_tcp_init(uv_default_loop(), &server);

    R_ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT, &addr));
    R_ASSERT(0 == uv_tcp_bind(&server, (const struct sockaddr*) &addr));
    R_ASSERT(0 == uv_listen((uv_stream_t*) & server, RD_MAX_CONNECTIONS, on_connect));

    R_INFO("(%5d) listening on port ", TEST_PORT);

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    free(resbuf.base);
    
    return 0;
}


