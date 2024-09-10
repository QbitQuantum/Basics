static inline void write_thread_traces(struct exception_handler_data *data)
{
	THREADENTRY32 entry = {0};
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,
			GetCurrentProcessId());
	bool success;

	if (snapshot == INVALID_HANDLE_VALUE)
		return;

	entry.dwSize = sizeof(entry);
	success = !!Thread32First(snapshot, &entry);

	while (success) {
		write_thread_trace(data, &entry);
		success = !!Thread32Next(snapshot, &entry);
	}

	CloseHandle(snapshot);
}