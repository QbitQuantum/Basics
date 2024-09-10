static 
void log_write_impl(const char *file, int line, const char *log_level_str, const char *format, va_list ap) {
	char buf_text[1024];
	char buf_time[32];
	memset(buf_text, 0, sizeof(buf_text));
	memset(buf_time, 0, sizeof(buf_time));
	int count_text;
	int count_time;

	/**
	* thus, no need to call a system call gettid() everytime
	*/
	static __thread int t_tid = -1;

	if(t_tid == -1) {
		t_tid = gettid();
	}
	
	count_text = sprintf(buf_text, " %-6s %d %s:%d ", log_level_str, t_tid, file, line);
	count_text += vsprintf(buf_text + count_text, format, ap);
	if(buf_text[count_text-1] != '\n') {
		buf_text[count_text] = '\n';
		buf_text[++count_text] = '\0';
	} else {
		buf_text[count_text] = '\0';
	}

	time_info_t ti;
	
	while(1) {
		pthread_mutex_lock(&mutex);

		/****************************************************************/
		/**
		 * 这个地方可以优化一下
		 * 当第一次失败后，返回来在写日志的时候，又重新写了一遍时间
		 * 是否合理，还需要在仔细琢磨一下
		 */
		ti = get_cur_time();

		count_time = sprintf(buf_time, "[ %02d:%02d:%02d.%06ld ]", ti.hour, ti.min, ti.sec, ti.usec);

		/****************************************************************/

		/**
		* create a new log file
		*/
		if(ti.day_num > cur_log_day_num) {
			g_new_fd = 1;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		}
		/**
		* buf is full
		*/
		if(w_buf->pos + count_time + count_text >= MAX_BUF_SIZE) {
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		} else {
			strncpy(w_buf->buf+w_buf->pos, buf_time, count_time);
			w_buf->pos += count_time;
			strncpy(w_buf->buf+w_buf->pos, buf_text, count_text);
			w_buf->pos += count_text;
			
			pthread_mutex_unlock(&mutex);
			break;
		}
	}
}