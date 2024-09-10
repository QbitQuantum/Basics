////////////////////////////////////////////////////////////////////////////////////////////////////
// Fills specified SHELLEXECUTEINFO structure with the information read from registry
VOID CConfigReader::PopulateExecuteInformation ( SHELLEXECUTEINFO* pExecInfo )
{
    pExecInfo->cbSize = sizeof ( SHELLEXECUTEINFO ) ;
    pExecInfo->fMask = 
        SEE_MASK_FLAG_DDEWAIT | SEE_MASK_HMONITOR | SEE_MASK_NOASYNC | SEE_MASK_UNICODE ;
    pExecInfo->hwnd = NULL ;
    pExecInfo->lpVerb = g_szShellExecuteVerb ;
    pExecInfo->lpFile = m_lpszPath ;
    pExecInfo->lpParameters = m_lpszParams ;
    pExecInfo->lpDirectory = NULL ;
    pExecInfo->nShow = m_dwWindowState ;

    // Set monitor handle. 0 means primary monitor, if index is greater then zero we will enumerate
    // through all monitors and find the required one using index. 
    if ( 0 < m_dwMonitorIndex )
    {
        FINDMONITOR FindMonitor ;
        FindMonitor.dwCurrentIndex = 0 ;
        FindMonitor.dwRequiredIndex = m_dwMonitorIndex ;
        FindMonitor.hMonitor = NULL ;
        EnumDisplayMonitors ( NULL , NULL , EnumMonitorsCallBack , ( LPARAM ) &FindMonitor ) ;
        if ( NULL != FindMonitor.hMonitor )
        {
            pExecInfo->hMonitor = FindMonitor.hMonitor ;
            return ;
        }
    } // If index is invalid or is 0 we will default to primary monitor
    else
    {
        POINT ptZero = { 0 } ;
        pExecInfo->hMonitor = MonitorFromPoint ( ptZero , MONITOR_DEFAULTTOPRIMARY ) ;
    }
}