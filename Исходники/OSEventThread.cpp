void OSEventThread::Entry()
{
    int n;
    fd_set rfds;
    struct timeval tv;
    struct timeval * ptv = NULL;

    ULONG lasttime = OS::GetTickCount();
    ULONG currtime = lasttime;

    init_wakeuper();

    while (!IsStopRequested()) {

        //10 check time rollback
        lasttime = currtime;
        currtime = OS::GetTickCount();
        if(currtime < lasttime) {
            rollback_timer(currtime);
            firePending();
        }

        //20 calc timeout
        if (-1 == calcNextTimeout(&tv,currtime)) {
            // no pending timers; block indefinitely
            TRACE("~~~~ no timers; blocking indefinitely ~~~~\n");
            ptv = NULL;
        } else {
            TRACE("~~~~ blocking for %ds + %dus ~~~~\n", (int)tv.tv_sec, (int)tv.tv_usec);
            ptv = &tv;
        }

        //30 make local copy of read fd_set
        memcpy(&rfds, &mReadFds, sizeof(fd_set));

        //40 select
        n = select(mMaxfFd, &rfds, NULL, NULL, ptv);

        TRACE("~~~~ %d events fired ~~~~\n", n);
        
        if(n > 0){

            //50 Check for read-ready
            processReadReadies(&rfds, n);

        }else if(n == 0){

            //60 Check for timeouts
            processTimeouts();

        }else{

            //70 check error
            int err = OSThread::GetErrno();
            switch(err)
            {
            case EINTR:
                continue;
            case EBADF:
                WARN("event_req: EBADF\n");
				continue;
            case ENOTCONN:
                ERR("event_req: ENOTCONN\n");
                continue;
            default:
                ERR("event_req: select error (%d)\n", err);
                ASSERT_C(0);
                return;
            }
        }


        //80 Fire away
        firePending();
    }

    uninit_wakeuper();

    TRACE("~~~~ Thread exit:%x ~~~~\n",(unsigned int)GetCurrentThreadID());
}