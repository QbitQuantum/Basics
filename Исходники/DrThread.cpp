DWORD DrTimerThread::ThreadEntry()
{
    DWORD currentTime;
    int timeToExpire;
    DrJob * timer;

    while (true)
    {
        //Analyse the current state of the timer heap
        Lock();

        currentTime=GetTickCount();
        while (true)
        {
            timer = (DrJob*) m_timerHeap.PeekHeapRoot();

            //If there are no more timers on the heap then our timeout on our event
            //is infinite and we're done checking the heap
            if (timer==NULL)
            {
                m_dwTimerThreadSleepPeriod=INFINITE;
                break;
            }

            //Looks like we've got a timer. Work out when it'll expire relative to now
            LogAssert(timer->m_isActiveTimer);
            timeToExpire=(int ) (timer->m_expiryTime-currentTime);

            //If it hasn't expired yet then that should be our timeout and we're done
            //checking the heap
            if (timeToExpire>0)
            {
                m_dwTimerThreadSleepPeriod=(DWORD)timeToExpire;
                break;
            }

            //Looks like we've got an expired timer. Mark is as no longer active, pop it from heap
            //and pass it to a worker thread for processing
            timer->m_isActiveTimer=false;
            m_timerHeap.DequeueHeapRoot();
            BOOL fSuccess = m_pPool->EnqueueJob(timer, currentTime, NULL);
            LogAssert(fSuccess);
        }

        //Little wrinkle here. We don't want to wake up too often and we don't care
        //to be all that accurate for expiring timers. Therefore, if timeout is
        //too small we'll push it out in the hope of expiring more timers at once
        if (m_dwTimerThreadSleepPeriod<c_TimerExpirySlopPeriod)
        {
            m_dwTimerThreadSleepPeriod=c_TimerExpirySlopPeriod;
        }
        m_timerThreadWakesAt=currentTime+m_dwTimerThreadSleepPeriod;

        ResetEvent(m_timerEventHandle);

        Unlock();

        //Above should have set timeout for an appropriate value. Sleep waiting for that time
        //to expire or to be told we have a new head of the heap timer
        WaitForSingleObject(m_timerEventHandle, m_dwTimerThreadSleepPeriod);

        //Possible we were woken because the thread pool is being shut down so check that case
        if (m_pPool->ShouldQuit())
        {
            break;
        }

    }

    //Treat any timers still scheduled as if they were cancelled
    Lock();

    while (true)
    {
        timer = (DrJob*) m_timerHeap.DequeueHeapRoot();
        if (timer==NULL)
        {
            break;
        }
        LogAssert(timer->m_isActiveTimer==true);
        timer->m_isActiveTimer=false;
    }

    Unlock();

    return 0;
}