void MachineThreads::gatherConservativeRoots(ConservativeRoots& conservativeRoots, void* stackCurrent)
{
    gatherFromCurrentThread(conservativeRoots, stackCurrent);

    if (m_threadSpecific) {
        PlatformThread currentPlatformThread = getCurrentPlatformThread();

        MutexLocker lock(m_registeredThreadsMutex);

#ifndef NDEBUG
        // Forbid malloc during the gather phase. The gather phase suspends
        // threads, so a malloc during gather would risk a deadlock with a
        // thread that had been suspended while holding the malloc lock.
        fastMallocForbid();
#endif
        for (Thread* thread = m_registeredThreads; thread; thread = thread->next) {
            if (!equalThread(thread->platformThread, currentPlatformThread))
                suspendThread(thread->platformThread);
        }

        // It is safe to access the registeredThreads list, because we earlier asserted that locks are being held,
        // and since this is a shared heap, they are real locks.
        for (Thread* thread = m_registeredThreads; thread; thread = thread->next) {
            if (!equalThread(thread->platformThread, currentPlatformThread))
                gatherFromOtherThread(conservativeRoots, thread);
        }

        for (Thread* thread = m_registeredThreads; thread; thread = thread->next) {
            if (!equalThread(thread->platformThread, currentPlatformThread))
                resumeThread(thread->platformThread);
        }

#ifndef NDEBUG
        fastMallocAllow();
#endif
    }
}