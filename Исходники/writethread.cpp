void WriteThread::Stop()
{
    stopped = false;
    closeport(wFD);
}