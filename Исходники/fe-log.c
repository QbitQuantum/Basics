static void log_single_line(WINDOW_REC *window, const char *server_tag,
			    const char *target, int level, const char *text)
{
	char windownum[MAX_INT_STRLEN];
	LOG_REC *log;

	if (window != NULL) {
		/* save to log created with /WINDOW LOG */
		ltoa(windownum, window->refnum);
		log = logs_find_item(LOG_ITEM_WINDOW_REFNUM,
				     windownum, NULL, NULL);
		if (log != NULL)
			log_write_rec(log, text, level);
	}

	log_file_write(server_tag, target, level, text, FALSE);
}