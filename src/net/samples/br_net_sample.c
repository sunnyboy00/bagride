
#include "uv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "br_net.h"
#include "tt.h"

static int on_udp_parse(ssize_t nread_, const uv_buf_t* inbuf_, br_udp_server_t* pserver_) {
    TT_INFO("udp (%d)[%d] %s data (%p)", pserver_->m_port, (int) nread_,
            inbuf_->base,
            pserver_->m_data);
    return 0;
}

static int on_tcp_parse(ssize_t nread_, const uv_buf_t* inbuf_, br_tcp_server_t* pserver_) {
    TT_INFO("tcp (%d)[%d] %s data (%p)", pserver_->m_port, (int) nread_, inbuf_->base,
            pserver_->m_data);
    asprintf(&pserver_->m_write_buffer.base, "<<%s>>", inbuf_->base);
    pserver_->m_write_buffer.len = strlen(pserver_->m_write_buffer.base);
    return 0;
}

#define RESPONSE1 \
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Content-Length: 13\r\n" \
  "\r\n" \
  "hello1 world\n"

#define RESPONSE2 \
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Content-Length: 13\r\n" \
  "\r\n" \
  "hello2 world\n"

static int gen_hello_response1_cb(br_http_client_t* cli_) {
    cli_->m_resbuf.base = strdup(RESPONSE1);
    cli_->m_resbuf.len = sizeof (RESPONSE1);
    return 0;
}

static int gen_hello_response2_cb(br_http_client_t* cli_) {
    cli_->m_resbuf.base = strdup(RESPONSE2);
    cli_->m_resbuf.len = sizeof (RESPONSE2);
    return 0;
}

br_tcp_server_t tcp_servers[] = {
    {
        .m_port = 6969,
        .m_user_parse_cb = on_tcp_parse
    },
    { .m_port = 7070,
        .m_user_parse_cb = on_tcp_parse}
};

br_udp_server_t udp_servers[] = {
    {
        .m_port = 7171,
        .m_user_parse_cb = on_udp_parse
    },
    { .m_port = 7272,
        .m_user_parse_cb = on_udp_parse}
};

br_http_server_t http_servers[] = {
    {
        .m_port = 7373,
        .m_gen_response_cb = gen_hello_response1_cb
    },
    {
        .m_port = 7474,
        .m_gen_response_cb = gen_hello_response2_cb
    }
};

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    br_udp_register(udp_servers, sizeof (udp_servers) / sizeof (br_udp_server_t));
    br_tcp_register(tcp_servers, sizeof (tcp_servers) / sizeof (br_tcp_server_t));
    br_http_register(http_servers, sizeof (http_servers) / sizeof (br_http_server_t));

    br_run();
    return 0;

}