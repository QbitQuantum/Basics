UINT CALLBACK CFileMonitor::MonitorThread( VOID * aArgs )
{
    CFileMonitor * monitor = (CFileMonitor *)aArgs;
    while ( WAIT_IO_COMPLETION == WaitForSingleObjectEx( monitor->m_hEventStop , INFINITE  , TRUE ) );

    InterlockedDecrement( &monitor->m_uTotalThread );
    _endthreadex( TRUE );
    return TRUE;
}