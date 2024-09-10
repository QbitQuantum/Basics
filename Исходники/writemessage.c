int writemessage(int sock,char *buffer,int msglen,int to,int fromchild) 
{
    int     retcode ;
    char    ent[40] ;
    int     nfds ;
    fd_set  selectmask ; /* Select mask */
    struct timeval    wait_timer;

    int     msgsize ;
    int     msgsend ;
    int     nbsent ;

    if ( fromchild == 1 ) {
        sprintf(ent,"Child %06d : ",getpid()) ;
    } else {
        strcpy(ent,"") ;
    }
    nbsent = 0 ;
    msgsize = msglen ;
/*
** start the writing loop
*/
    while ( nbsent < msgsize ) {
        nfds = sysconf(_SC_OPEN_MAX) ;
        FD_ZERO(&selectmask) ;
        FD_SET(sock,&selectmask) ;
        wait_timer.tv_sec  = to ;
        wait_timer.tv_usec = 0 ;
        if ( (retcode = select(FD_SETSIZE,0,&selectmask,0,&wait_timer) ) == -1 ) {
            /*
            ** Select error
            */
            if (debug ) 
                printmessage(stderr,CASE_NORMAL,0,timestamp,"%sWrite message : Select error : MSG (%d,%d)\n",ent,msglen,nbsent) ;
            return -1 ;
        } else if ( retcode == 0 ) {
            if (debug ) 
                printmessage(stderr,CASE_NORMAL,0,timestamp,"%sWrite message : Time Out : MSG (%d,%d)\n",ent,msglen,nbsent) ;
            return -1 ;
        } else {
            msgsend = write(sock,&buffer[nbsent],msgsize-nbsent) ;
            if ( msgsend < 0 ) {
                if (debug ) 
                    printmessage(stderr,CASE_NORMAL,0,timestamp,"%sWrite message : Send error %d(%s) : MSG (%d,%d)\n",ent,errno,strerror(errno),msglen,nbsent) ;
                return -1 ;
            } else if (msgsend  == 0 ) {
                if (debug ) 
                    printmessage(stderr,CASE_NORMAL,0,timestamp,"%sWrite message : Connection breaks : MSG (%d,%d)\n",ent,msglen,nbsent) ;
                return -1 ;
            } else {
                nbsent = nbsent + msgsend ;
            }
        }
    }
    return(0) ;
}