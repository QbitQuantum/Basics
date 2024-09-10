void Drive::Umount(HWND)
{
	// check mounted
	CheckMounted();
//	if (GetDriveType(mnt) == DRIVE_NO_ROOT_DIR)
//		mounted = false;
	if (!mounted)
		throw truntime_error(_T("Cannot unmount a not mounted drive"));

	// unmount
	fuse_unmount(wchar_to_utf8_cstr(mnt).c_str(), NULL);

	if (subProcess) {
		// attach console to allow sending ctrl-c
		AttachConsole(subProcess->pid);

		// disable ctrl-c to not exit this process
		SetConsoleCtrlHandler(HandlerRoutine, TRUE);

		if (!GenerateConsoleCtrlEvent(CTRL_C_EVENT, subProcess->pid)
		    && !GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, subProcess->pid))
			TerminateProcess(subProcess->hProcess, 0);

		// force exit
		if (WaitForSingleObject(subProcess->hProcess, 2000) == WAIT_TIMEOUT)
			TerminateProcess(subProcess->hProcess, 0);
			
		// close the console
		FreeConsole();
		SetConsoleCtrlHandler(HandlerRoutine, FALSE);
	}
	CheckMounted();
}