void run_proc(std::string command_line) {
	report_info("Running: " + command_line);
	// execute the process
	STARTUPINFO startup_info = { 0 };
	startup_info.cb = sizeof(startup_info);
	PROCESS_INFORMATION process_info = { 0 };
	CreateProcessW(NULL, const_cast<char16 *>(utf8::cvt<std::wstring>(command_line).c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info);
	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
}