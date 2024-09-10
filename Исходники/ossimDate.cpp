ossimLocalTm ossimLocalTm::convertToGmt()const
{
  m_mutex.lock();
   struct tm gmt = *this;
#if !defined(_MSC_VER) 
   tzset();
#else
   _tzset();
#endif

#if ( defined(__APPLE__) || defined(__FreeBSD__)  || defined(__OpenBSD__) )
   gmt.tm_sec -= tm_gmtoff; // Seconds east of UTC
#elif (defined(WIN32))
   long timezoneOffset=0;
   _get_timezone(&timezoneOffset);
   //m_timezoneOffset = timezone; // Seconds west of UTC
   if ( tm_isdst )
   {
      timezoneOffset -= 3600; // Subtract an hour.
   }
   m_timezoneOffset = -timezoneOffset;
#else
   m_timezoneOffset = timezone; // Seconds west of UTC
   if ( tm_isdst )
   {
      m_timezoneOffset -= 3600; // Subtract an hour.
   }
   m_timezoneOffset = -m_timezoneOffset;
#endif
   
   time_t t = mktime(&gmt);
   std::tm localTime = *localtime(&t);

m_mutex.unlock();
   ossimLocalTm result(localTime);
   
   return result;
}