# simpleclog
a simple log lib for c

The base code is copy from antirez's redis, and I modified it. :D
the base code in antirez's redis:
server.c
void serverLogRaw(int level, const char *msg) 
void serverLog(int level, const char *fmt, ...)

##usage
log(CIB_ERROR, "xxx %d", 1);

You need change 
sysparam.logfile[0]
sysparam.loglevel
in cibLogRaw and cibLog to your own log file and level.
