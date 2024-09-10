void sys_execute(const char *p_command, const char *p_argument)
{
	char t_command_line[1024];
	sprintf(t_command_line, "\"%s\" %s", p_command, p_argument);

	STARTUPINFOA t_startup_info;
	memset(&t_startup_info, 0, sizeof(STARTUPINFOA));
	t_startup_info . cb = sizeof(STARTUPINFOA);
	t_startup_info . dwFlags = STARTF_USESHOWWINDOW;
	t_startup_info . wShowWindow = SW_HIDE;

	PROCESS_INFORMATION t_process_info;
	if (CreateProcessA(p_command, t_command_line, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &t_startup_info, &t_process_info) != 0)
	{
		CloseHandle(t_process_info . hThread);
		WaitForSingleObject(t_process_info . hProcess, INFINITE);
		CloseHandle(t_process_info . hProcess);
	}
}