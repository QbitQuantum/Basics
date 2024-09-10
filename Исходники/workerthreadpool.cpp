void WorkerThreadPool::stopAllThreads()
{
    QTime timer;
    long timeout = 60 * 1000;

    timer.start();
#if 0
    while(true) {

        int size = 0;
        threadListMutex.lock();
        size = workingThreads.size();
        threadListMutex.unlock();

        if(size <= 0)
            break;

        //deliver thread finished events to us
        //QCoreApplication::sendPostedEvents(pub,WorkerThreadEvent::ThreadIdle);
        QThread::msleep(10);

        /* If we hit this, we waited long enough, maybe the threads
         * are somehow blocked. We need to force quit them
         */
        if(timer.elapsed() > timeout) {
            threadListMutex.lock();
            for(auto i = workingThreads.begin();
                    i != workingThreads.end(); i++) {

                WorkerThread* th = i.value();
                th->terminate();
                th->wait(1000);
                delete th;

            }
            workingThreads.clear();
            threadListMutex.unlock();
            break;
        }

    }
#endif
    timeout = 10 * 1000;

    //quit all threads
    QMutexLocker l(&threadListMutex);
    for(int i= 0; i < threads.size(); i++) {
        WorkerThread* th = threads.takeAt(i);
        th->shutdown();
        bool finished = th->wait(timeout);
        if(!finished) {
            th->terminate();
            finished = th->wait(timeout);

            //@BUG what to do if the thread can not be terminated
            if(!finished)
                qDebug()<<"Could not stop thread correctly";
        }
        delete th;
    }
}