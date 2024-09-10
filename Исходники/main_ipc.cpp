int Rusock()
{
    unlink("./USOCK");
    CSocket sock;
    nRet = sock.Listen("./USOCK");
    if (nRet < 0)
    {
        printf("Listen failed:%s \n", strerror(errno));
        return -1;
    }

    int fd = sock.Accept();
    if (nRet < 0)
    {
        printf("Accept failed:%s \n", strerror(errno));
        return -1;
    }

    while (true)
    {
        if (_HandleSignal() < 0)
            break;

        gettimeofday(&time_a, NULL);
        nRet = read(fd, rbuff, g_len);
        gettimeofday(&time_b, NULL);
        struct timeval *time_w = (struct timeval *)(rbuff);

        if (nRet != g_len)
        {
            printf("read fialed nRet %d %s\n", nRet, strerror(errno));
            break;
        }
        g_count0++;

        if(g_verify == 1)
        {
            struct data* d = (struct data* )(rbuff+sizeof(struct timeval));
            if( d->compare() < 0)
            {
                printf("format error %s\n");fflush(NULL);
            }
        }

        unsigned long long use_time0 = (time_b.tv_sec - time_a.tv_sec) * 1000000 + (time_b.tv_usec - time_a.tv_usec);
        total_time0 += use_time0;

        unsigned long long delay_time = (time_b.tv_sec - time_w->tv_sec) * 1000000 + (time_b.tv_usec - time_w->tv_usec);
        if(delay_time < 10000)
        {
            if(delay_time > g_delay_max)
                g_delay_max = delay_time;
            recv_delay_count0++;
            recv_delay0 += delay_time;
        }
    }

    return 0;
}