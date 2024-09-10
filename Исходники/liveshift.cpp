void LiveShiftSource::LOG(char const *fmt, ... )
{
  if (m_log != NULL)
  {
#if defined(TARGET_WINDOWS)
    // determine the current local time
    SYSTEMTIME utcSystemTime;
    GetSystemTime(&utcSystemTime);
    SYSTEMTIME systemTime;
    SystemTimeToTzSpecificLocalTime(NULL, &utcSystemTime, &systemTime);
    
    // log nicely formatted log message
    fprintf(m_log, "%02d:%02d:%02d.%03d\t", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

    // log passed-in string
    va_list ap; 
    va_start (ap, fmt); 
    vfprintf(m_log, fmt, ap); 
    va_end(ap); 

    fflush(m_log);
#else
    // log passed-in string
    va_list ap; 
    va_start (ap, fmt); 
    vfprintf(m_log, fmt, ap); 
    va_end(ap); 

    fflush(m_log);
#endif
  }
} 