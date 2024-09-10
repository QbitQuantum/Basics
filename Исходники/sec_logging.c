void DDS_Security_log (unsigned   log_level,
		       const char *message,
		       const char *category)
{
	struct timeval	tv;
	FILE		*f;
	struct tm	tm_data, *tm;
	char		tmbuf [40];
	DDS_LogInfo	log_info;

	if (!log_options_set || log_level < log_options.log_level)
		return;

	if (!log_options.log_file && !log_options.distribute) {
		log_printf (SEC_ID, log_level, "%s: %s\r\n", category, message);
		return;
	}
	if (log_options.log_file) {
		if (openf (f, logname, "a")) {
			gettimeofday (&tv, NULL);
#ifdef _WIN32
			_localtime32_s (&tm_data, &tv.tv_sec);
			tm = &tm_data;
#else
			tm = localtime_r (&tv.tv_sec, &tm_data);
			if (!tm) {
#ifdef LOG_DATE
				fprintf (f, "\?\?\?\?-\?\?\?-\?\? ");
#endif
				fprintf (f, "\?\?:\?\?:\?\?.\?\?\? ");
			}
			else
#endif
			{
				tmbuf [0] = '\0';
#ifdef LOG_DATE
				strftime (tmbuf, sizeof (tmbuf), "%Y-%m-%d ", tm);
#endif
				strftime (&tmbuf [strlen (tmbuf)],
						sizeof (tmbuf) - strlen (tmbuf),
						"%H:%M:%S.", tm);
				snprintf (&tmbuf [strlen (tmbuf)],
					  sizeof (tmbuf) - strlen (tmbuf),
					  "%03lu ", (unsigned long) tv.tv_usec / 1000);
				fprintf (f, "%s", tmbuf);
			}
			fprintf (f, "%s: %s\r\n", category, message);
			fclose (f);
		}
	}
	if (log_options.distribute && log_writer) {
		log_info.log_level = log_level;
		log_info.message = (char *) message;
		log_info.category = (char *) category;
		DDS_DataWriter_write (log_writer, &log_info, 0);
	}
}