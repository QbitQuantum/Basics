int send_message(char * msg, char * from, char ** recipients, int num_recipients)
{
    /*	...Adds Date:
    	...Adds Message-Id:*/
    int r;
    int wstat;
    int i;
    struct tm * dt;
    unsigned long msgwhen;
    FILE * fdm;
    FILE * fde;
    pid_t pid;
    int pim[2];				/*message pipe*/
    int pie[2];				/*envelope pipe*/
    FILE *mfp;
    char msg_buffer[256];

    /*open a pipe to qmail-queue*/
    if(pipe(pim)==-1 || pipe(pie)==-1) {
        return -1;
    }
    pid = vfork();
    if(pid == -1) {
        /*failure*/
        return -1;
    }
    if(pid == 0) {
        /*I am the child*/
        close(pim[1]);
        close(pie[1]);
        /*switch the pipes to fd 0 and 1
          pim[0] goes to 0 (stdin)...the message*/
        if(fcntl(pim[0],F_GETFL,0) == -1) {
            /*			fprintf(stderr,"Failure getting status flags.\n");*/
            _exit(120);
        }
        close(0);
        if(fcntl(pim[0],F_DUPFD,0)==-1) {
            /*			fprintf(stderr,"Failure duplicating file descriptor.\n");*/
            _exit(120);
        }
        close(pim[0]);
        /*pie[0] goes to 1 (stdout)*/
        if(fcntl(pie[0],F_GETFL,0) == -1) {
            /*			fprintf(stderr,"Failure getting status flags.\n");*/
            _exit(120);
        }
        close(1);
        if(fcntl(pie[0],F_DUPFD,1)==-1) {
            /*			fprintf(stderr,"Failure duplicating file descriptor.\n");*/
            _exit(120);
        }
        close(pie[0]);
        if(chdir(QMAIL_LOCATION) == -1) {
            _exit(120);
        }
        execv(*binqqargs,binqqargs);
        _exit(120);
    }

    /*I am the parent*/
    fdm = fdopen(pim[1],"wb");					/*updating*/
    fde = fdopen(pie[1],"wb");
    if(fdm==NULL || fde==NULL) {
        return -1;
    }
    close(pim[0]);
    close(pie[0]);

    /*prepare to add date and message-id*/
    msgwhen = time(NULL);
    dt = gmtime((long *)&msgwhen);
    /*start outputting to qmail-queue
      date is in 822 format
      message-id could be computed a little better*/
    fprintf(fdm,"Date: %u %s %u %02u:%02u:%02u -0000\nMessage-ID: <%lu.%u.blah>\n"
            ,dt->tm_mday,montab[dt->tm_mon],dt->tm_year+1900,dt->tm_hour,dt->tm_min,dt->tm_sec,msgwhen,getpid() );

    mfp = fopen( msg, "rb" );

    while ( fgets( msg_buffer, sizeof(msg_buffer), mfp ) != NULL )
    {
        fprintf(fdm,"%s",msg_buffer);
    }

    fclose(mfp);

    fclose(fdm);


    /*send the envelopes*/

    fprintf(fde,"F%s",from);
    fwrite("",1,1,fde);					/*write a null char*/
    for(i=0; i<num_recipients; i++) {
        fprintf(fde,"T%s",recipients[i]);
        fwrite("",1,1,fde);					/*write a null char*/
    }
    fwrite("",1,1,fde);					/*write a null char*/
    fclose(fde);

    /*wait for qmail-queue to close*/
    do {
        r = wait(&wstat);
    } while ((r != pid) && ((r != -1) || (errno == EINTR)));
    if(r != pid) {
        /*failed while waiting for qmail-queue*/
        return -1;
    }
    if(wstat & 127) {
        /*failed while waiting for qmail-queue*/
        return -1;
    }
    /*the exit code*/

    if((wstat >> 8)!=0) {
        /*non-zero exit status
          failed while waiting for qmail-queue*/
        return -1;
    }
    return 0;
}