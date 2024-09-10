int
osip_trace(char *filename_long, int li, osip_trace_level_t level, FILE * f, char *chfr, ...)
{
#ifdef ENABLE_TRACE
	va_list ap;
	int relative_time = 0;

  char *fi=NULL;
  
  if (filename_long!=NULL) {
    fi = strrchr(filename_long, '/');
    if (fi==NULL)
      fi = strrchr(filename_long, '\\');
    if (fi!=NULL)
      fi++;
    if (fi==NULL)
      fi=filename_long;
  }
                              
#if (defined(WIN32)  && !defined(_WIN32_WCE)) || defined(__linux)
	static struct timeval start = { 0, 0 };
	struct timeval now;

	if (start.tv_sec == 0 && start.tv_usec == 0) {
		__osip_port_gettimeofday(&start, NULL);
	}
	__osip_port_gettimeofday(&now, NULL);

	relative_time = 1000 * (now.tv_sec - start.tv_sec);
	if (now.tv_usec - start.tv_usec > 0)
		relative_time = relative_time + ((now.tv_usec - start.tv_usec) / 1000);
	else
		relative_time = relative_time - 1 + ((now.tv_usec - start.tv_usec) / 1000);
#endif

#if !defined(WIN32) && !defined(SYSTEM_LOGGER_ENABLED)
	if (logfile == NULL && use_syslog == 0 && trace_func == NULL) {	/* user did not initialize logger.. */
		return 1;
	}
#endif

	if (tracing_table[level] == LOG_FALSE)
		return OSIP_SUCCESS;

	if (f == NULL && trace_func == NULL)
		f = logfile;

	VA_START(ap, chfr);

#if  defined(__VXWORKS_OS__) || defined(__rtems__)
	/* vxworks can't have a local file */
	f = stdout;
#endif

	if (0) {}
#ifdef ANDROID
	else if (trace_func == 0) {
		int lev;

		switch(level){
	case OSIP_INFO3:	lev = ANDROID_LOG_DEBUG;	break;
	case OSIP_INFO4:	lev = ANDROID_LOG_DEBUG;	break;
	case OSIP_INFO2:	lev = ANDROID_LOG_INFO;	break;
	case OSIP_INFO1:	lev = ANDROID_LOG_INFO;	break;
	case OSIP_WARNING:	lev = ANDROID_LOG_WARN;	break;
	case OSIP_ERROR:	lev = ANDROID_LOG_ERROR;	break;
	case OSIP_BUG:	lev = ANDROID_LOG_FATAL;	break;
	case OSIP_FATAL:	lev = ANDROID_LOG_FATAL;	break;
	default:		lev = ANDROID_LOG_DEFAULT;	break;
		}
		__android_log_vprint(lev, "osip2", chfr, ap);
	}
#elif defined(__APPLE__)  && defined(__OBJC__)
	else if (trace_func == 0) {
		char buffer[MAX_LENGTH_TR];
		int in = 0;
		
		memset(buffer, 0, sizeof(buffer));
		if (level == OSIP_FATAL)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| FATAL | <%s: %i> ", fi, li);
		else if (level == OSIP_BUG)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "|  BUG  | <%s: %i> ", fi, li);
		else if (level == OSIP_ERROR)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| ERROR | <%s: %i> ", fi, li);
		else if (level == OSIP_WARNING)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "|WARNING| <%s: %i> ", fi, li);
		else if (level == OSIP_INFO1)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO1 | <%s: %i> ", fi, li);
		else if (level == OSIP_INFO2)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO2 | <%s: %i> ", fi, li);
		else if (level == OSIP_INFO3)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO3 | <%s: %i> ", fi, li);
		else if (level == OSIP_INFO4)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO4 | <%s: %i> ", fi, li);
		
		vsnprintf(buffer + in, MAX_LENGTH_TR-1 - in, chfr, ap);
		NSLog(@"%s", buffer);
	}
#endif
	else if (f && use_syslog == 0) {
		if (level == OSIP_FATAL)
			fprintf(f, "| FATAL | %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_BUG)
			fprintf(f, "|  BUG  | %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_ERROR)
			fprintf(f, "| ERROR | %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_WARNING)
			fprintf(f, "|WARNING| %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_INFO1)
			fprintf(f, "| INFO1 | %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_INFO2)
			fprintf(f, "| INFO2 | %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_INFO3)
			fprintf(f, "| INFO3 | %i <%s: %i> ", relative_time, fi, li);
		else if (level == OSIP_INFO4)
			fprintf(f, "| INFO4 | %i <%s: %i> ", relative_time, fi, li);

		vfprintf(f, chfr, ap);

		fflush(f);
	} else if (trace_func) {
		trace_func(fi, li, level, chfr, ap);
	}

#if defined (HAVE_SYSLOG_H) && !defined(__arc__)
	else if (use_syslog == 1) {
		char buffer[MAX_LENGTH_TR];
		int in = 0;

		memset(buffer, 0, sizeof(buffer));
		if (level == OSIP_FATAL)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| FATAL | <%s: %i> ", fi, li);
		else if (level == OSIP_BUG)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "|  BUG  | <%s: %i> ", fi, li);
		else if (level == OSIP_ERROR)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| ERROR | <%s: %i> ", fi, li);
		else if (level == OSIP_WARNING)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "|WARNING| <%s: %i> ", fi, li);
		else if (level == OSIP_INFO1)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO1 | <%s: %i> ", fi, li);
		else if (level == OSIP_INFO2)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO2 | <%s: %i> ", fi, li);
		else if (level == OSIP_INFO3)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO3 | <%s: %i> ", fi, li);
		else if (level == OSIP_INFO4)
			in = snprintf(buffer, MAX_LENGTH_TR-1, "| INFO4 | <%s: %i> ", fi, li);

		vsnprintf(buffer + in, MAX_LENGTH_TR-1 - in, chfr, ap);
		if (level == OSIP_FATAL)
			syslog(LOG_ERR, "%s", buffer);
		else if (level == OSIP_BUG)
			syslog(LOG_ERR, "%s", buffer);
		else if (level == OSIP_ERROR)
			syslog(LOG_ERR, "%s", buffer);
		else if (level == OSIP_WARNING)
			syslog(LOG_WARNING, "%s", buffer);
		else if (level == OSIP_INFO1)
			syslog(LOG_INFO, "%s", buffer);
		else if (level == OSIP_INFO2)
			syslog(LOG_INFO, "%s", buffer);
		else if (level == OSIP_INFO3)
			syslog(LOG_DEBUG, "%s", buffer);
		else if (level == OSIP_INFO4)
			syslog(LOG_DEBUG, "%s", buffer);
	}
#endif
#ifdef SYSTEM_LOGGER_ENABLED
	else {
		char buffer[MAX_LENGTH_TR];
		int in = 0;
#ifdef DISPLAY_TIME
		int relative_time;
#endif

		memset(buffer, 0, sizeof(buffer));
		if (level == OSIP_FATAL)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "| FATAL | %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_BUG)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "|  BUG  | %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_ERROR)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "| ERROR | %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_WARNING)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "|WARNING| %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_INFO1)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "| INFO1 | %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_INFO2)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "| INFO2 | %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_INFO3)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "| INFO3 | %i <%s: %i> ", relative_time,
						   fi, li);
		else if (level == OSIP_INFO4)
			in = _snprintf(buffer, MAX_LENGTH_TR-1, "| INFO4 | %i <%s: %i> ", relative_time,
						   fi, li);

		_vsnprintf(buffer + in, MAX_LENGTH_TR-1 - in, chfr, ap);
#ifdef UNICODE
		{
			WCHAR wUnicode[MAX_LENGTH_TR*2];
			MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wUnicode,
								MAX_LENGTH_TR*2);
			OutputDebugString(wUnicode);
		}
#else
		OutputDebugString(buffer);
#endif
	}
#endif

	va_end(ap);
#endif
	return OSIP_SUCCESS;
}