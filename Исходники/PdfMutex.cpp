bool PdfMutex::TryLock()
{
#ifdef PODOFO_MULTI_THREAD
#ifdef _WIN32
    return (TryEnterCriticalSection( &m_cs ) ? true : false);
#else
    int nRet = pthread_mutex_trylock( &m_mutex );
    if( nRet == 0 )
	    return true;
    else if( nRet == EBUSY )
	    return false;
    else
    {
	    PODOFO_RAISE_ERROR( ePdfError_MutexError );
    }
#endif // _WIN32
#endif // PODOFO_MULTI_THREAD

    // If we have no multithreading support always
    // simulate succesfull locking
    return true;
}