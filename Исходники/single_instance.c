/*
return
    0:  还没运行
    <0: 出错
    >0: 已运行
*/
int
already_running(void)
{
    int                 fd;
    char                buf[16];

    fd = fopen(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if(fd < 0){
        syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
        return -1;
    }

    if(lockfile(fd) < 0){
        if(errno == EACCES || errno == EAGAIN){/*已运行了*/
            close(fd);
            return 1;
        }
        syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
        return -2;
    }

    ftruncate(fd, 0);/*将文件长度截短为0*/
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);  /*将运行的进程号写到文件中*/
    return 0;   /**/
}