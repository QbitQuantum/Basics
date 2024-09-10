int __cdecl main(int argc_ansi, char** argv_ansi)
{
	DWORD size;
	register HANDLE mutex, stdout;
	stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	mutex = OpenMutexA(SYNCHRONIZE, FALSE, "Global/Rufus_CmdLine");
	if (mutex == NULL)
		goto error;
	WaitForSingleObject(mutex, INFINITE);
	goto out;

error:
	WriteFile(stdout, error_msg, sizeof(error_msg), &size, 0);

out:
	ExitProcess(0);
}