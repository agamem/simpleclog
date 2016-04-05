/*
 * File:   ciblog.h
 * Author: agamem
 *
 * Created on 2013年11月30日, 下午9:10
 */

#ifndef CIBLOG_H
#define	CIBLOG_H

#define CIB_TRACE 0
#define CIB_DEBUG 1
#define CIB_WARN 2
#define CIB_INFO 3
#define CIB_ERROR 4
#define CIB_LOG_RAW (1<<10)

#define CIB_MAX_LOGMSG_LEN 1024

#define log(level,format,...) cibLog(level, "[%s@%s,%d] "format, __func__, __FILE__, __LINE__, ##__VA_ARGS__ )


void cibLog(int level, const char *fmt, ...);
void cibLogRaw(int level, const char *msg);
char * ArrayToStr(const char *input, int len);

#endif	/* CIBLOG_H */

