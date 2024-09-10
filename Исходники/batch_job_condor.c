static batch_job_id_t batch_job_condor_wait (struct batch_queue * q, struct batch_job_info * info_out, time_t stoptime)
{
	static FILE *logfile = 0;

	if(!logfile) {
		logfile = fopen(q->logfile, "r");
		if(!logfile) {
			debug(D_NOTICE, "couldn't open logfile %s: %s\n", q->logfile, strerror(errno));
			return -1;
		}
	}

	while(1) {
		/*
		   Note: clearerr is necessary to clear any cached end-of-file condition,
		   otherwise some implementations of fgets (i.e. darwin) will read to end
		   of file once and then never look for any more data.
		 */

		clearerr(logfile);

		char line[BATCH_JOB_LINE_MAX];
		while(fgets(line, sizeof(line), logfile)) {
			int type, proc, subproc;
			batch_job_id_t jobid;
			time_t current;
			struct tm tm;

			struct batch_job_info *info;
			int logcode, exitcode;

			if(sscanf(line, "%d (%" SCNbjid ".%d.%d) %d/%d %d:%d:%d", &type, &jobid, &proc, &subproc, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) == 9) {
				tm.tm_year = 2008 - 1900;
				tm.tm_isdst = 0;

				current = mktime(&tm);

				info = itable_lookup(q->job_table, jobid);
				if(!info) {
					info = malloc(sizeof(*info));
					memset(info, 0, sizeof(*info));
					itable_insert(q->job_table, jobid, info);
				}

				debug(D_BATCH, "line: %s", line);

				if(type == 0) {
					info->submitted = current;
				} else if(type == 1) {
					info->started = current;
					debug(D_BATCH, "job %" PRIbjid " running now", jobid);
				} else if(type == 9) {
					itable_remove(q->job_table, jobid);

					info->finished = current;
					info->exited_normally = 0;
					info->exit_signal = SIGKILL;

					debug(D_BATCH, "job %" PRIbjid " was removed", jobid);

					memcpy(info_out, info, sizeof(*info));
					free(info);
					return jobid;
				} else if(type == 5) {
					itable_remove(q->job_table, jobid);

					info->finished = current;

					fgets(line, sizeof(line), logfile);
					if(sscanf(line, " (%d) Normal termination (return value %d)", &logcode, &exitcode) == 2) {
						debug(D_BATCH, "job %" PRIbjid " completed normally with status %d.", jobid, exitcode);
						info->exited_normally = 1;
						info->exit_code = exitcode;
					} else if(sscanf(line, " (%d) Abnormal termination (signal %d)", &logcode, &exitcode) == 2) {
						debug(D_BATCH, "job %" PRIbjid " completed abnormally with signal %d.", jobid, exitcode);
						info->exited_normally = 0;
						info->exit_signal = exitcode;
					} else {
						debug(D_BATCH, "job %" PRIbjid " completed with unknown status.", jobid);
						info->exited_normally = 0;
						info->exit_signal = 0;
					}

					memcpy(info_out, info, sizeof(*info));
					free(info);
					return jobid;
				}
			}
		}


		if(itable_size(q->job_table) <= 0)
			return 0;

		if(stoptime != 0 && time(0) >= stoptime)
			return -1;

		if(process_pending())
			return -1;

		sleep(1);
	}

	return -1;
}