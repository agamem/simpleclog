#include <syslog.h>
#include "stdinc.h"
#include "ciblog.h"
#include "cibplay.h"
#include "boardset.h"
#include "zmalloc.h"


//输出日志
void cibLogRaw(int level, const char *msg)
{

    const char *c = "TDWIE";
    FILE *fp;
    char buf[64];
    int rawmode = (level & CIB_LOG_RAW);
    int log_to_stdout = sysparam.logfile[0] == '\0';

    level &= 0xff; /* clear flags */
    if (level < sysparam.loglevel) return;

    fp = log_to_stdout ? stdout : fopen(sysparam.logfile, "a");
    if (!fp) return;

    if (rawmode)
    {
        fprintf(fp, "%s", msg);
    }
    else
    {
        int off;
        struct timeval tv;

        gettimeofday(&tv, NULL);
        off = strftime(buf, sizeof(buf), "%d %b %H:%M:%S.", localtime(&tv.tv_sec));
        snprintf(buf + off, sizeof(buf) - off, "%03d", (int)tv.tv_usec / 1000);
        fprintf(fp, "[%d] %s %c %s\n", (int)getpid(), buf, c[level], msg);
    }
    fflush(fp);

    if (!log_to_stdout) fclose(fp);
    //if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
}

void cibLog(int level, const char *fmt, ...)
{
    va_list ap;
    char msg[CIB_MAX_LOGMSG_LEN];

    if ((level & 0xff) < sysparam.loglevel) return;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    cibLogRaw(level, msg);
}
char * ArrayToStr(const char* chs, int len)
{
//用于接收到的串转换成要用的十六进制串返回主窗口调用
    char hex[17] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', ' '};
    char *ascii = (char*)zcalloc ( (len * 3 + 1) * sizeof(char) ); // calloc ascii

    int i = 0;
    while ( i < len )
    {
        ascii[i * 3] = hex[chs[i] >> 4] ;
        ascii[i * 3 + 1] = hex[chs[i] & 0x0F] ;
        ascii[i * 3 + 2] = hex[16];
        ++i;
    }
    return ascii;                    // ascii 返回之前未释放
}


