#include "br_trace.h"

#include <stdio.h>
#include <stdarg.h>
/*#include <unistd.h>*/

#pragma GCC diagnostic ignored "-Wmissing-format-attribute"

static int rtrace_max_level = 2;

static const char* rtrace_levels_strings[] = {" ERR", "WARN", "INFO"};

void rtrace(int level_, const char *file_, int line_, const char *format_, ...) {
    if (level_ > rtrace_max_level) return;
    else {

        va_list ap;
        fprintf(stderr, "[%s] ", rtrace_levels_strings[level_]);

        va_start(ap, format_);
        vfprintf(stderr, format_, ap);
        va_end(ap);
       
        (2 > level_) ? fprintf(stderr,"\t\t%s:%d\n", file_, line_): fprintf(stderr,"\n");
    }
}

void rtrace_level(int level_){
    if( level_ <= 2) rtrace_max_level = level_;
}