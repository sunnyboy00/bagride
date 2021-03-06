#ifndef BR_NET_H
#define	BR_NET_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "uv.h"
#include "http_parser.h"
    
    
#define br_buf_t uv_buf_t
#define br_tcp_t uv_tcp_t
#define br_udp_t uv_udp_t
    
#define BR_MAX_CONNECTIONS 64
   
/**
 * tcp
 **/    
typedef struct br_tcp_server_s {
    int m_port;
    struct sockaddr_in m_socket;
    br_tcp_t m_handler;
    br_buf_t m_write_buffer;    
    void* m_user_parse_cb;
    void* m_data;
} br_tcp_server_t;

/**
 * parse incomming stream fragment
 * -> set write buffer if write required
 * -> return 0 on success
 */
typedef int (*br_tcp_server_parser_cb)(ssize_t nread_, const br_buf_t* pbuf_, 
        br_tcp_server_t* pserver_);

void br_tcp_register(br_tcp_server_t* tcp_servers_, int size_);

/**
 * udp
 **/    
typedef struct br_udp_server_s {
    int m_port;
    struct sockaddr_in m_socket;
    br_udp_t m_handler;
    void* m_user_parse_cb;
    void* m_data;
} br_udp_server_t;

typedef int (*br_udp_server_parser_cb)(ssize_t nread_, const br_buf_t* pbuf_, 
        br_udp_server_t* pserver_);


void br_udp_register(br_udp_server_t* udp_servers_, int size_);

/**
 * http
 */
typedef struct br_http_server_s {
    struct sockaddr_in m_addr;
    uv_tcp_t m_handler;
    http_parser_settings m_parser_settings;
    int m_request_num;
    int m_port;
    void* m_gen_response_cb;
} br_http_server_t;

typedef struct br_http_client_s {
    uv_tcp_t m_handle;
    http_parser m_parser;
    uv_write_t m_write_req;
    int m_request_num;
    br_http_server_t* m_server;
    uv_buf_t m_resbuf;
} br_http_client_t;

typedef int (*br_http_server_parser_cb)(br_http_client_t* cli_);

void br_http_register(br_http_server_t* servers_, int size_);

/**
 * common
 */
void br_run(void);
void br_stop(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BR_NET_H */

