void
NewTrap(char *name)
{
	int	rc;
	char	buf[128];

	sprintf(buf, "Unimplemented API: %s\n\nPress OK to continue execution,\npress Cancel to quit application", name);
	rc = MessageBox((HWND)NULL, buf, "Trap", MB_ICONEXCLAMATION | MB_OKCANCEL);
	if ( rc == IDCANCEL )
		FatalExit(0);
}