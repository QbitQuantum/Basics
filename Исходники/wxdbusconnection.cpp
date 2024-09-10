dbus_bool_t DBusThread::add_watch(DBusWatch *watch, void *data)
{
	DBusThread * thread = (DBusThread *) data;

	if (!thread->CalledFromThread()) {
		char tmp = 0;
		safe_write(thread->m_wakeup_pipe[1], &tmp, 0);
		thread->EnterCriticalSection();
	}
	else if (!thread->m_thread_holds_lock)
		thread->EnterCriticalSection();

	WatchesList &watches = *thread->GetWatchesList();
	watches.push_back(watch);

	if (!thread->CalledFromThread())
		thread->LeaveCriticalSection();
	else if (!thread->m_thread_holds_lock)
		thread->LeaveCriticalSection();

	return true;
}