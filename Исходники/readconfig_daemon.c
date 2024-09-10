/*
 * 检测守护进程是否已经运行
 */
int already_running() {
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0) {
        syslog(LOG_ERR, "cannt open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    } else {
        printf("open lockfile fail\n");
    }

    // 注意设置LOCK_NB为非阻塞的，未获取锁时返回出错
    // 为什么lockfile不能上锁？？？　其他进程实例仍然可以加锁
    if (lockfile(fd) < 0) {
        printf("lock file fali, maybe daemon has already run?\n");
        if (errno == EACCES || error == EAGAIN) {
            close(fd);
        }
        syslog(LOG_ERR, "cannot lock %s, %s" , LOCKFILE, strerror(errno));
        exit(1);
    } else {
        printf("lock file success\n");
    }

    printf("start daemon\n");
    // 向文件中写入pid
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
}