bool CFileSystemMonitor::AnyChanges() {
  if (_scraper_directory_on_a_network_drive) {
    // Network mapped drives are unsupported
    write_log(Preferences()->debug_filesystem_monitor(), "[CFileSystemMonitor] Unsupported network mapped drive\n");
    write_log(Preferences()->debug_filesystem_monitor(), "[CFileSystemMonitor] Treating as \"no changes\"\n");
    return false;
  }
	// http://msdn.microsoft.com/en-us/library/windows/desktop/ms687025(v=vs.85).aspx
	dwWaitStatus = WaitForMultipleObjects(
		1,                // number of handles
		&dwChangeHandle,  // handle
		FALSE,            // bWaitAll - does not make a difference here
		0);               // time to wait
	if (dwWaitStatus == WAIT_OBJECT_0) {
		write_log(Preferences()->debug_filesystem_monitor(), "[CFileSystemMonitor] Scraper directoy changed.\n");
		// Resetting change handle for next query
		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa365261%28v=vs.85%29.aspx
		FindNextChangeNotification(dwChangeHandle);
		return true;
	}
	write_log(Preferences()->debug_filesystem_monitor(), "[CFileSystemMonitor] No changes in scraper directoy.\n");
	return false;
}