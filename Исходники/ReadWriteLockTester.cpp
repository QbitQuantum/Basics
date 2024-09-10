void ReadWriteLockTester::doRead() {
    LockScoper scoper(m_pReadLock);
    scoper.lock();
    try {
        
        //printf("In read lock of thread %ld\n", getCurrentThreadId());
        //Block forvever
        //while (1) {
        //    ;
        //}
        
        printf("Read value %d at thread %ld\n", m_valueToTestRead, getCurrentThreadId());
    } catch (std::exception& e) {
        printf("Exception occurred %s\n", e.what());
    }
}