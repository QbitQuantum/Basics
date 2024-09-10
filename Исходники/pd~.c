static void pd_tilde_close(t_pd_tilde *x)
{
#ifdef _WIN32
    int termstat;
#endif
    if (x->x_outfd)
        fclose(x->x_outfd);
    if (x->x_infd)
        fclose(x->x_infd);
    if (x->x_childpid > 0)
#ifdef _WIN32
        _cwait(&termstat, x->x_childpid, WAIT_CHILD);
#else
        waitpid(x->x_childpid, 0, 0);
#endif
    if (x->x_msgbuf)
        free(x->x_msgbuf);
    x->x_infd = x->x_outfd = 0;
    x->x_childpid = -1;
    x->x_msgbuf = 0;
    x->x_msgbufsize = 0;
}