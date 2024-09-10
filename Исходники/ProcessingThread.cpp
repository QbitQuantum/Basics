void ProcessingThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    releaseCapture();
    doStop=true;
}