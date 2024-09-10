int main() {

    int lock, condition, monitor, value, i;
    lock = CreateDistLock("DistLock", 8);
    condition = CreateDistCondition("DistCV",6);
    monitor = CreateDistMonitor("MonitorTest", 11, 10);

    AcquireDistLock(lock);
    /* Requires another program to be run that signals the lock*/
    WaitDistCondition(condition, lock);
    for(i = 0; i < 10; i++) {
        SetDistMonitor(monitor, i, i);
    }
    for(i = 0; i < 10; i++) {
        value = GetDistMonitor(monitor, i);
        PrintF("monitor[%d]: %d", sizeof("monitor[%d]: %d"), i, value);
    }
    DestroyDistMonitor(monitor);
    ReleaseDistLock(lock);
    DestroyCondition(condition);
    DestroyDistLock(lock);
}