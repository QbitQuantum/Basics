static void pickup_service(char *unused_buf, ssize_t unused_len,
			           char *unused_service, char **argv)
{
    SCAN_DIR *scan;
    char   *queue_name;
    PICKUP_INFO info;
    const char *path;
    char   *id;
    int     file_count;

    /*
     * Sanity check. This service takes no command-line arguments.
     */
    if (argv[0])
	msg_fatal("unexpected command-line argument: %s", argv[0]);

    /*
     * Skip over things that we don't want to open, such as files that are
     * still being written, or garbage. Leave it up to the sysadmin to remove
     * garbage. Keep scanning the queue directory until we stop removing
     * files from it.
     * 
     * When we find a file, stroke the watchdog so that it will not bark while
     * some application is keeping us busy by injecting lots of mail into the
     * maildrop directory.
     */
    queue_name = MAIL_QUEUE_MAILDROP;		/* XXX should be a list */
    do {
	file_count = 0;
	scan = scan_dir_open(queue_name);
	while ((id = scan_dir_next(scan)) != 0) {
	    if (mail_open_ok(queue_name, id, &info.st, &path) == MAIL_OPEN_YES) {
		pickup_init(&info);
		info.path = mystrdup(path);
		watchdog_pat();
		if (pickup_file(&info) == REMOVE_MESSAGE_FILE) {
		    if (REMOVE(info.path))
			msg_warn("remove %s: %m", info.path);
		    else
			file_count++;
		}
		pickup_free(&info);
	    }
	}
	scan_dir_close(scan);
    } while (file_count);
}