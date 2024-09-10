bool WatcherThread::unwatch(const Path& path)
{
    MutexLocker locker(&mutex);
    if (paths.remove(path)) {
        CFRunLoopSourceSignal(source);
        CFRunLoopWakeUp(loop);
        return true;
    }
    return false;
}