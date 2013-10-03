
#include "uv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "br_trace.h"

#define TEST_PORT1 6969

static uv_udp_t server1 = {0};
static struct sockaddr_in sock_addr1 = {0};

void on_udp_recv(uv_udp_t* handle_, ssize_t nread_, const uv_buf_t* buf_,
        const struct sockaddr* addr_, unsigned flags_) {

    (void) handle_;
    (void) addr_;
    (void) flags_;

    if (nread_ > 0) {
        R_INFO("[1] (%lu) %s", nread_, buf_->base);
    }
    R_INFO("free  :%lu %p", buf_->len, buf_->base);
    free(buf_->base);
}

void on_alloc(uv_handle_t* client_, size_t suggested_size_, uv_buf_t* buf_) {
    buf_->base = calloc(1, suggested_size_);
    buf_->len = suggested_size_;
    (void) client_;
    R_INFO("malloc:%lu %p", buf_->len, buf_->base);
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    R_ASSERT(0 == uv_udp_init(uv_default_loop(), &server1));
    R_ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT1, &sock_addr1));
    R_ASSERT(0 == uv_udp_bind(&server1, (const struct sockaddr*) &sock_addr1, 0));
    R_ASSERT(0 == uv_udp_recv_start(&server1, on_alloc, on_udp_recv));
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    return 0;
}