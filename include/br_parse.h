#ifndef _BR_PARSE_H
#define	_BR_PARSE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

 typedef struct br_substring_s {
        const char* start;
        const char* end;
        size_t n;
    } br_substring_t;

    typedef struct br_line_s {
        const char* p;
        const char* start;
        const char* sub_start;
        int n;
        const char* end;
        br_substring_t sub;
        char sep;
    } br_line_t;

    int br_line_prepare(const char* _start, size_t _n, char _sep, br_line_t* _io);

    br_substring_t* br_line_next_substring(br_line_t* _io);
    
    
#ifdef __cplusplus
}
#endif

#endif /* _BR_PARSE_H */