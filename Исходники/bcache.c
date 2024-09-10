int getnewutmpent( struct user_info *up)
{
    int utmpfd;
    struct user_info *uentp;
    time_t  now;
    int     i, n, num[2];
    FILE * fp;

    fp=fopen(ULIST, "rw+");
    utmpfd = fileno(fp);
    if (utmpfd < 0)
        return -1;

    flock(utmpfd, LOCK_EX);

    resolve_utmp();
    flock(utmpfd, LOCK_EX);
    if (utmpshm->max_login_num < count_users)
        utmpshm->max_login_num = count_users;
    for (i = 0; i < USHM_SIZE; i++)
    {
        uentp = &(utmpshm->uinfo[i]);
        if (!uentp->active || !uentp->pid)
            break;
    }
    if (i >= USHM_SIZE)
    {
        flock(utmpfd, LOCK_UN);
        close(utmpfd);/* add by yiyo */
        return -2;
    }
    utmpshm->uinfo[i] = *up;

    now = time(0);
    if (now > utmpshm->uptime + 60)
    {
        num[0] = num[1] = 0;
        utmpshm->uptime = now;
        for (n = 0; n < USHM_SIZE; n++)
        {
            uentp = &(utmpshm->uinfo[n]);
            if (uentp->active && uentp->pid)
            {
                //web登陆没有守护进程，pid没有意义，所以，不检测web的pid
                if (uentp->mode < 20000 && kill(uentp->pid, 0) == -1)
                {
                    //huangxu@071220:貌似不能这样
                    //kill(uentp->pid, 9);
                    //memset(uentp, 0, sizeof(struct user_info));
                    continue;
                }
                else
                {
                    num[(uentp->invisible == YEA) ? 1 : 0]++;
                    //huangxu@071203:这个数组有嘛用？还是尝试清0吧。
                    //memset(uentp, 0, sizeof(struct user_info));
                    //todo:需要一个专门的函数处理时间计算。
                }
            }
        }
        utmpshm->usersum = allusers();
        n = USHM_SIZE - 1;
        while (n > 0 && utmpshm->uinfo[n].active == 0)
            n--;
        ftruncate(utmpfd, 0);
        write(utmpfd, utmpshm->uinfo, (n + 1) * sizeof(struct user_info));
    }
    flock(utmpfd, LOCK_UN);
    close(utmpfd);
    return i + 1;
}