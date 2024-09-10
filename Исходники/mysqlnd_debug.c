/* {{{ mysqlnd_debug::log */
static enum_func_status
MYSQLND_METHOD(mysqlnd_debug, log)(MYSQLND_DEBUG * self,
								   unsigned int line, const char * const file,
								   unsigned int level, const char * type, const char * message)
{
	char pipe_buffer[512];
	enum_func_status ret;
	int i;
	char * message_line;
	unsigned int message_line_len;
	unsigned int flags = self->flags;
	char pid_buffer[10], time_buffer[30], file_buffer[200],
		 line_buffer[6], level_buffer[7];
	MYSQLND_ZTS(self);

#ifdef MYSQLND_THREADED
	if (MYSQLND_G(thread_id) != tsrm_thread_id()) {
		return PASS; /* don't trace background threads */
	}
#endif

	if (!self->stream) {
		if (FAIL == self->m->open(self, FALSE)) {
			return FAIL;
		}
	}

	if (level == -1) {
		level = zend_stack_count(&self->call_stack);
	}
	i = MIN(level, sizeof(pipe_buffer) / 2  - 1);
	pipe_buffer[i*2] = '\0';
	for (;i > 0;i--) {
		pipe_buffer[i*2 - 1] = ' ';
		pipe_buffer[i*2 - 2] = '|';
	}


	if (flags & MYSQLND_DEBUG_DUMP_PID) {
		snprintf(pid_buffer, sizeof(pid_buffer) - 1, "%5u: ", self->pid);
		pid_buffer[sizeof(pid_buffer) - 1 ] = '\0';
	}
	if (flags & MYSQLND_DEBUG_DUMP_TIME) {
		/* The following from FF's DBUG library, which is in the public domain */
#if defined(PHP_WIN32)
		/* FIXME This doesn't give microseconds as in Unix case, and the resolution is
		in system ticks, 10 ms intervals. See my_getsystime.c for high res */
		SYSTEMTIME loc_t;
		GetLocalTime(&loc_t);
		snprintf(time_buffer, sizeof(time_buffer) - 1,
				 /* "%04d-%02d-%02d " */
				 "%02d:%02d:%02d.%06d ",
				 /*tm_p->tm_year + 1900, tm_p->tm_mon + 1, tm_p->tm_mday,*/
				 loc_t.wHour, loc_t.wMinute, loc_t.wSecond, loc_t.wMilliseconds);
		time_buffer[sizeof(time_buffer) - 1 ] = '\0';
#else
		struct timeval tv;
		struct tm *tm_p;
		if (gettimeofday(&tv, NULL) != -1) {
			if ((tm_p= localtime((const time_t *)&tv.tv_sec))) {
				snprintf(time_buffer, sizeof(time_buffer) - 1,
						 /* "%04d-%02d-%02d " */
						 "%02d:%02d:%02d.%06d ",
						 /*tm_p->tm_year + 1900, tm_p->tm_mon + 1, tm_p->tm_mday,*/
						 tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec,
						 (int) (tv.tv_usec));
				time_buffer[sizeof(time_buffer) - 1 ] = '\0';
			}
		}
#endif
	}
	if (flags & MYSQLND_DEBUG_DUMP_FILE) {
		snprintf(file_buffer, sizeof(file_buffer) - 1, "%14s: ", file);
		file_buffer[sizeof(file_buffer) - 1 ] = '\0';
	}
	if (flags & MYSQLND_DEBUG_DUMP_LINE) {
		snprintf(line_buffer, sizeof(line_buffer) - 1, "%5u: ", line);
		line_buffer[sizeof(line_buffer) - 1 ] = '\0';
	}
	if (flags & MYSQLND_DEBUG_DUMP_LEVEL) {
		snprintf(level_buffer, sizeof(level_buffer) - 1, "%4u: ", level);
		level_buffer[sizeof(level_buffer) - 1 ] = '\0';
	}

	message_line_len = spprintf(&message_line, 0, "%s%s%s%s%s%s%s%s\n",
								flags & MYSQLND_DEBUG_DUMP_PID? pid_buffer:"",
								flags & MYSQLND_DEBUG_DUMP_TIME? time_buffer:"",
								flags & MYSQLND_DEBUG_DUMP_FILE? file_buffer:"",
								flags & MYSQLND_DEBUG_DUMP_LINE? line_buffer:"",
								flags & MYSQLND_DEBUG_DUMP_LEVEL? level_buffer:"",
								pipe_buffer, type? type:"", message);

	ret = php_stream_write(self->stream, message_line, message_line_len)? PASS:FAIL;
	efree(message_line);
	if (flags & MYSQLND_DEBUG_FLUSH) {
		self->m->close(self);
		self->m->open(self, TRUE);	
	}
	return ret;
}