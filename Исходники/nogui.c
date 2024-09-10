/* @TODO : this code is for a part duplicated from gui/src/c/xsci/inter.c
with some stuff removed (TCL/TK and a few other things)
*/
int Xorgetchar(int interrupt){
    int i;
    int inter_max_plus1 = 0;
    static fd_set Select_mask_ref;
    static fd_set select_mask;
    static fd_set Write_mask_ref;
    static fd_set write_mask;
    static struct timeval select_timeout;
    static int fd_in=0,fd_out=0,fd_err=0 ;
    static int state = 0;
    fd_in = fileno(stdin) ;
    fd_out = fileno(stdout);
    fd_err = fileno(stderr);

    FD_ZERO(&Select_mask_ref);
    FD_SET(fd_in , &Select_mask_ref);
    FD_ZERO(&Write_mask_ref);

    inter_max_plus1 = fd_in;

    inter_max_plus1 = Max(fd_out,inter_max_plus1);
    inter_max_plus1 = Max(fd_err,inter_max_plus1);
    inter_max_plus1++;

    for( ; ; ) {
        fflush(stdout);
        fflush(stderr);

        /* Initialize masks  */
        select_mask = Select_mask_ref;
        write_mask  = Write_mask_ref;

        select_timeout.tv_sec = 0;
        select_timeout.tv_usec = 10;
        i = select(inter_max_plus1, &select_mask, &write_mask, (fd_set *)NULL, &select_timeout);
        if (i < 0) {
            if (errno != EINTR) /* EINTR  A signal was caught. */
            {
                sciprint(_("Error. A signal has been caught.\n"));
                exit(0);
                continue;
            }
        }

        /* if there's something to output */
        if ( FD_ISSET(fd_out,&write_mask)) {
            fflush(stdout);
        }
        if ( FD_ISSET(fd_err,&write_mask)) {
            fflush(stderr);
        }

        /* if there's something to read */
        if (FD_ISSET(fd_in,&select_mask))
            state=1;

        if (state) {
            i=getchar();
            if (i==LF) state=0;
            return(i);
        }

        if (interrupt&&(ismenu()==1)) return(-1);

    }
}