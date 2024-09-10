void
mongoc_log_default_handler (mongoc_log_level_t  log_level,
                            const char         *log_domain,
                            const char         *message,
                            void               *user_data)
{
   struct timeval tv;
   struct tm tt;
   time_t t;
   FILE *stream;
   char nowstr[32];
   int pid;

   bson_gettimeofday(&tv, NULL);
   t = tv.tv_sec;

#ifdef _WIN32
#  ifdef _MSC_VER
     localtime_s(&tt, &t);
#  else
     tt = *(localtime(&t));
#  endif
#else
   localtime_r(&t, &tt);
#endif

   strftime (nowstr, sizeof nowstr, "%Y/%m/%d %H:%M:%S", &tt);

   switch (log_level) {
   case MONGOC_LOG_LEVEL_ERROR:
   case MONGOC_LOG_LEVEL_CRITICAL:
   case MONGOC_LOG_LEVEL_WARNING:
      stream = stderr;
      break;
   case MONGOC_LOG_LEVEL_MESSAGE:
   case MONGOC_LOG_LEVEL_INFO:
   case MONGOC_LOG_LEVEL_DEBUG:
   case MONGOC_LOG_LEVEL_TRACE:
   default:
      stream = stdout;
   }

#ifdef __linux__
   pid = syscall (SYS_gettid);
#elif defined(_WIN32)
   pid = (int)_getpid ();
#else
   pid = (int)getpid ();
#endif

   fprintf (stream,
            "%s.%04ld: [%5d]: %8s: %12s: %s\n",
            nowstr,
            tv.tv_usec / 1000L,
            pid,
            mongoc_log_level_str(log_level),
            log_domain,
            message);
}