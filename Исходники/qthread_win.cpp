void QAdoptedThread::init()
{
    d_func()->handle = GetCurrentThread();
    d_func()->id = GetCurrentThreadId();
}