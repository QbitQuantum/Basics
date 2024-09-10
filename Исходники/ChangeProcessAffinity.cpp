// ////////////////////////////////////////////////////////////////////////////
//	CODE NOTE: To be moved into ProcessId.cpp
unsigned int ProcessNameToProcessId(const std::string &process_name,
	std::vector<ProcessId> &process_id_list, unsigned int max_count)
{
#ifdef _Windows
	unsigned int               pid_count           = 0;
	unsigned int               pid_count_allocated = 8192;
	boost::shared_array<DWORD> pid_list(new DWORD[pid_count_allocated]);

	do {
		DWORD current_size = pid_count_allocated * sizeof(DWORD);
		DWORD needed_size  = 0;
		if (!::EnumProcesses(pid_list.get(), current_size, &needed_size))
			ThrowSystemError("Call to EnumProcesses() failed");
		//	We assume that if the number of bytes used is less than the number
		//	allocated that we've received the entire list of process ids.
		//	Otherwise, we re-allocate and re-try the operation.
		if (needed_size < current_size) {
			pid_count = needed_size / sizeof(DWORD);
			break;
		}
		pid_count_allocated *= 2;
		pid_list.reset(new DWORD[pid_count_allocated]);
	} while (pid_count_allocated);

	std::vector<ProcessId> tmp_process_id_list;
	unsigned int           done_count = 0;
	unsigned int           count_1;

	for (count_1 = 0; count_1 < pid_count; ++count_1) {
		HANDLE process_handle;
		if ((process_handle = ::OpenProcess(PROCESS_SET_INFORMATION |
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
			pid_list[count_1])) != NULL) {
			//	First module is main EXE, so only need an array of one...
			HMODULE module_handle;
			DWORD   needed_size;
			if (::EnumProcessModules(process_handle, &module_handle,
				sizeof(module_handle), &needed_size) != 0) {
				char module_name[(MaxPathNameLength * 2) + 1];
				if (::GetModuleBaseName(process_handle, module_handle, module_name,
					sizeof(module_name) - 1) != 0) {
					if (!stricmp(process_name.c_str(), module_name)) {
						try {
							tmp_process_id_list.push_back(pid_list[count_1]);
							++done_count;
						}
						catch (...) {
							::CloseHandle(process_handle);
							throw;
						}
					}
				}
			}
			::CloseHandle(process_handle);
			if (max_count && (done_count >= max_count))
				break;
		}
	}

	if (!tmp_process_id_list.size())
		ThrowException("Function 'ProcessNameToProcessId()' was unable to "
			"locate a process named '" + process_name + "'.");

	process_id_list.swap(tmp_process_id_list);

	return(static_cast<unsigned int>(process_id_list.size()));
#else
	ThrowException("Function 'ProcessNameToProcessId()' not yet supported "
		"under this operating system.");

	return(0);
#endif // #ifdef _Windows
}