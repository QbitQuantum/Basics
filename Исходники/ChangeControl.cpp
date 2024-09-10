///////////////////////////////////////////////////////////////////////////////
// UpdateInterestBits - Update the interest (desired notifications) for the given observer
Error CSubject::UpdateInterestBits( IObserver* pObserver, u32 uInIntrestBits )
{
    // No need to check for pObs being nonzero since the find below guarantees correct work in any case
    Error curError = Errors::Failure;

#if SUPPORT_CONCURRENT_ATTACH_DETACH_TO_SUBJECTS
    SpinWait::Lock lock(m_observerListMutex);
#endif

    // Find the given observer in our observer list
    ObserverList::iterator it = std::find(m_observerList.begin(), m_observerList.end(), pObserver);
    if ( it != m_observerList.end() )
    {
#if SUPPORT_CONCURRENT_ATTACH_DETACH_TO_SUBJECTS
        // We are under the lock in this case
        it->m_interestBits |= inInterest;
#else
        // No lock is used, but updates can happen concurrently. So use interlocked operation
        long prevBits;
        long newBits = long(it->m_interestBits | uInIntrestBits);
        do {
            prevBits = it->m_interestBits;
        } while ( _InterlockedCompareExchange((long*)&it->m_interestBits, newBits, prevBits) != prevBits );
#endif
        curError = Errors::Success;
    }

    return curError;
}