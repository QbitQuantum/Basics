static time_t check_file(LinphoneCoreManager* mgr)  {

	time_t cur_time = get_current_time();
	char*    filepath = linphone_core_compress_log_collection(mgr->lc);
	time_t  log_time = -1;
	uint32_t timediff = 0;
	FILE *file = NULL;

	BC_ASSERT_PTR_NOT_NULL(filepath);

	if (filepath != NULL) {
		int line_count = 0;
		char *line = NULL;
		size_t line_size = 256;
#ifndef WIN32
		struct tm tm_curr = {0};
		time_t time_prev = 0;
#endif

#if HAVE_ZLIB
		// 0) if zlib is enabled, we must decompress the file first
		file = gzuncompress(filepath);
#else
		file = fopen(filepath, "rb");
#endif
		BC_ASSERT_PTR_NOT_NULL(file);
		if (!file) return 0;
		// 1) expect to find folder name in filename path
		BC_ASSERT_PTR_NOT_NULL(strstr(filepath, bc_tester_writable_dir_prefix));

		// 2) check file contents
		while (getline(&line, &line_size, file) != -1) {
			// a) there should be at least 25 lines
			++line_count;
#ifndef WIN32
			// b) logs should be ordered by date (format: 2014-11-04 15:22:12:606)
			if (strlen(line) > 24) {
				char date[24] = {'\0'};
				memcpy(date, line, 23);
				/*reset tm_curr to reset milliseconds and below fields*/
				memset(&tm_curr, 0, sizeof(struct tm));
				if (strptime(date, "%Y-%m-%d %H:%M:%S", &tm_curr) != NULL) {
					tm_curr.tm_isdst = -1; // LOL
					log_time = mktime(&tm_curr);
					BC_ASSERT_TRUE(log_time >= time_prev);
					time_prev = log_time;
				}
			}
#endif
		}
		BC_ASSERT_TRUE(line_count > 25);
		free(line);
		fclose(file);
		ms_free(filepath);


		timediff = labs((long int)log_time - (long int)cur_time);
		(void)timediff;
#ifndef WIN32
		BC_ASSERT_TRUE( timediff <= 1 );
		if( !(timediff <= 1) ){
			char buffers[2][128] = {{0}};
			strftime(buffers[0], sizeof(buffers[0]), "%Y-%m-%d %H:%M:%S", localtime(&log_time));
			strftime(buffers[1], sizeof(buffers[1]), "%Y-%m-%d %H:%M:%S", localtime(&cur_time));

			ms_error("log_time: %ld (%s), cur_time: %ld (%s) timediff: %u"
				, (long int)log_time, buffers[0]
				, (long int)cur_time, buffers[1]
				, timediff
			);
		}
#else
		ms_warning("strptime() not available for this platform, test is incomplete.");
#endif
	}
	// return latest time in file
	return log_time;
}