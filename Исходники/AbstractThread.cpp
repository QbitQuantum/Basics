void AbstractThread::setPriority( const int32_t priority )
{
    TLockMutex l( m_mutex );
    
    if ( isState( ThreadState_Running ) )
    {
        setThreadPriority( m_thread, priority );
    }
}