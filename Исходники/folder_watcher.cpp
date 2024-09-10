void folder_watcher::force_stop()
{
	runs_ = false;
	TerminateThread(thread_, 0);
}