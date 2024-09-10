	void directory_monitor_update()
	{
		for (size_t index = 0; index < _monitor_state->records.size(); ++index)
		{
			DirectoryMonitorRecord* record = _monitor_state->records[index];
			directory_monitor_read_changes(record);

			// Instead of using SleepEx, we use MsgWaitForMultiple here to
			// allow the completion routine to be called.
			MsgWaitForMultipleObjectsEx(0, NULL, 0, QS_ALLINPUT, MWMO_ALERTABLE);
		}
	} // directory_monitor_update