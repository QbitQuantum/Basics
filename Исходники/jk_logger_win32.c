static int JK_METHOD jk2_logger_win32_log(jk_env_t *env, jk_logger_t *l,                                 
                                 int level,
                                 const char *what)
{
    HANDLE h=RegisterEventSource(NULL,JAKARTA_EVENT_SOURCE);
    LPCTSTR *Buffer;
    Buffer=&what;
    if( h==NULL ) {
        return JK_ERR;
    }
    if(l && l->level <= level && what) {       
        if( level == JK_LOG_DEBUG_LEVEL ) {
            ReportEvent(h,EVENTLOG_SUCCESS,0,MSG_DEBUG,NULL,1,0,Buffer,NULL);
        } else if( level == JK_LOG_INFO_LEVEL ) {
            ReportEvent(h,EVENTLOG_INFORMATION_TYPE,0,MSG_INFO,NULL,1,0,Buffer,NULL);
        } else if( level == JK_LOG_ERROR_LEVEL ){
            ReportEvent(h,EVENTLOG_WARNING_TYPE,0,MSG_ERROR,NULL,1,0,Buffer,NULL);
        } else if( level == JK_LOG_EMERG_LEVEL ){
            ReportEvent(h,EVENTLOG_ERROR_TYPE,0,MSG_EMERG,NULL,1,0,Buffer,NULL);
        }
    }
    DeregisterEventSource(h);
    
    return JK_OK;
}