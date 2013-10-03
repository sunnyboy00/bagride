
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "br_trace.h"

#define TEST_PORT 6969
#define RD_MAX_CONNECTIONS 64

static void on_close(uv_handle_t* handle_) {
    R_INFO("connection close");
    free(handle_);
}

static void on_alloc_buffer(uv_handle_t *handle_, size_t suggested_size_, uv_buf_t* buf_) {
    (void) handle_;
    buf_->base = (char*) calloc(suggested_size_, sizeof (char));
    buf_->len = suggested_size_;
}

static void on_after_write(uv_write_t* req_, int status_) {
    R_ASSERT(status_ >= 0);
    char *base = (char*) req_->data;
    free(base);
    free(req_);
}

static void on_read(uv_stream_t* stream_, ssize_t nread_, const uv_buf_t* buf_) {
    if (nread_ > 0) {
        R_INFO("[%d]\t%s", (int) nread_, buf_->base);
        uv_write_t *req = (uv_write_t *) calloc(1, sizeof (uv_write_t));
        req->data = (void*) buf_->base;

        /*buf_->len = nread_;*/
        uv_write(req, stream_, buf_, 1, on_after_write);

    } else {
        uv_close((uv_handle_t*) stream_, on_close);
    }
}

static void on_connect(uv_stream_t* pserver_, int status_) {
    R_ASSERT(status_ >= 0);
    uv_tcp_t *pclient = (uv_tcp_t*) calloc(1, sizeof (uv_tcp_t));
    uv_tcp_init(uv_default_loop(), pclient);

    if (uv_accept(pserver_, (uv_stream_t*) pclient) == 0) {
        uv_read_start((uv_stream_t*) pclient, on_alloc_buffer, on_read);
    } else {
        uv_close((uv_handle_t*) pclient, on_close);
    }
}

int main(int argc, char** argv) {

    (void) argc;
    (void) argv;

    struct sockaddr_in addr = {0};
    uv_tcp_t server;
    uv_tcp_init(uv_default_loop(), &server);

    R_ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT, &addr));
    R_ASSERT(0 == uv_tcp_bind(&server, (const struct sockaddr*) &addr));
    R_ASSERT(0 == uv_listen((uv_stream_t*) & server, RD_MAX_CONNECTIONS, on_connect));

    R_INFO("listening on port %d", TEST_PORT);

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);


    return 0;
}


