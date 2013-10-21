/* 
 * File:   log.h
 * Author: jam
 *
 * Created on 5 août 2013, 00:37
 */

#ifndef LOG_H
#define	LOG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define RTRACE_LEVEL_ERR  0
#define RTRACE_LEVEL_WARN 1
#define RTRACE_LEVEL_INFO 2

#define R_ASSERT(COND) if(!(COND)){rtrace(RTRACE_LEVEL_ERR, __FILE__, __LINE__, #COND); exit(1);}
   
#define R_INFO(b...) rtrace(RTRACE_LEVEL_INFO, __FILE__, __LINE__, b)    
#define R_WARN(b...) rtrace(RTRACE_LEVEL_WARN, __FILE__, __LINE__, b)    
#define R_ERR(b...)  rtrace(RTRACE_LEVEL_ERR, __FILE__, __LINE__, b)    
    
void rtrace_level(int level_);
void rtrace(int level_, const char *file_, int line_, const char *format_, ...);



#ifdef	__cplusplus
}
#endif

#endif	/* LOG_H */

