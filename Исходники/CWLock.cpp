BOOL CRWLockSlim::AcquireReaderLock( DWORD dwTimeout )
{
    BOOL bRet = FALSE;

#if ( _WIN32_WINNT_WIN7 <= _WIN32_WINNT )
    if ( INFINITE == dwTimeout || FALSE == m_bWin7AndLater )
    {
        AcquireSRWLockShared( &m_srwLock );
        bRet = TRUE;
    }
    else
    {
        LARGE_INTEGER lnCurr , lnEnd;
        QueryPerformanceCounter( &lnCurr );
        lnEnd.QuadPart = lnCurr.QuadPart + dwTimeout * ( m_lnFreq.QuadPart / 1000 );
        do
        {
            QueryPerformanceCounter( &lnCurr );
            bRet = (BOOL)TryAcquireSRWLockShared( &m_srwLock );
        } while ( lnCurr.QuadPart < lnEnd.QuadPart );
    }
#else
    AcquireSRWLockShared( &m_srwLock );
    bRet = TRUE;
#endif

    return bRet;
}