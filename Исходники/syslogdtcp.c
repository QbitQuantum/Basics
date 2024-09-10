// syslogdtcp( )
//
//  Entry into syslogdipc.cpp to setup and start UDP listening
//
void syslogdtcp(  )
{
    bool firststart = TRUE;
    int  msgrecv;
    int  seterr;
    int  i;
    char recv_buffer[1024];
    char *ptr_recv_buffer = recv_buffer;

    // setup for running, if error bug out - don't worry about main
    // will timeout waiting for TCPSEM1.
    seterr = setuptcp( );
    if(seterr)
    {
        if(seterr == 1)
        {
            psock_errno( NULL );
            closetcp( );
        }
        if(seterr == 3) printf("DosGetSharedMem failed\n");
    }

    // main working loop **********************
    while(TRUE)
    {
        // Just my play.  Set SEM1 (SYSLOGD is waiting), delay 1 sec
        // (let SYSLOGD reset), and start now FALSE - continue -
        // sleep 1.5 sec for SEM sets or thread will shutdown
        if(firststart)
        {
            DosPostEventSem(hevTCPSEM1); // tell main I am up!!
            DosSleep(1500);
            firststart = FALSE;
        }

        // clear recv_buffer
        for(i = 0; i < 1024; i++) recv_buffer[i] = 0;

        msgrecv = recv(tcpsocket, ptr_recv_buffer, 1024, 0);  // read socket

        // have a message msgrecv > 0 and not blocked
        if(msgrecv > 0 && prgoptions->securemode)
        {
            if(DosRequestMutexSem(mtxMEMMUX, 60000L) != 0)
            {
                printf("SYSLOGTCP: Timeout waiting for MUX\n");
            }
            else
            {
                if(pShareMem->slotstat[pShareMem->index])
                {
                    printf("SYSLOGTCP: Buffer full!!\n");
                    stats.tcpoverflows++;
                }
                else
                {
                    // clear the slot
                    strnset(pShareMem->data[pShareMem->index], '\0 ',
                                     sizeof(pShareMem->data[pShareMem->index]));

                    // write message into slot replace any character < 32 or > 126
                    // with a space RFC 3164 characters must be in this range
                    for(i = 0; i < strlen(recv_buffer); i++)
                    {
                        if(((int)recv_buffer[i] < 32) || ((int)recv_buffer[i] > 126))
                             pShareMem->data[pShareMem->index][i] = ' ';
                        else pShareMem->data[pShareMem->index][i] = recv_buffer[i];
                    }

                    // set flag slot has message
                    pShareMem->slotstat[pShareMem->index] = 1;

                    ++pShareMem->index;  // increment index to next slot
                    ++stats.systcprecvmsg;

                    // ++tcpatcount;

                    // if reached top of buffer reset index to 0 or bottom
                    if(pShareMem->index == (BUFFER_SLOTS)) pShareMem->index = 0;

                    DosPostEventSem(hevIDLESEM); // wakeup MAIN if IDE
                }
                DosReleaseMutexSem(mtxMEMMUX);
            }

        }  // end of msg recv


        // check for shutdown signal from main
        DosQueryEventSem(hevTCPSEM2, &TCPSEM2Ct);
        if(TCPSEM2Ct && !firststart)
        {
            DosResetEventSem(hevTCPSEM1, &TCPSEM1Ct);
            closetcp( );
        }

        // sleep 1 minute if blocked so do not suckup  the CPU
        if(!prgoptions->securemode) DosSleep(60000L);

    }  //$* end working loop

}  //$* end of syslogdtcp