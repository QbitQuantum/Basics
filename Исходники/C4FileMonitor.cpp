void C4FileMonitor::AddDirectory(const char * file)
{
	// Add IN_CLOSE_WRITE?
	int wd = inotify_add_watch(fd, file, IN_CREATE | IN_MODIFY | IN_MOVED_TO | IN_MOVE_SELF | IN_ONLYDIR);
	if (wd == -1)
		LogF("inotify_add_watch %s", strerror(errno));
	watch_descriptors[wd] = file;
}