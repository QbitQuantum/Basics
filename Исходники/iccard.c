static void
timerproc (HWND hwnd)
{
	HANDLE t;
	LUID l;
	int r;

	r = vmcall_iccard ();
	if (r > 0) {
		LockWorkStation ();
#if 0
		if (OpenProcessToken (GetCurrentProcess(),
				      TOKEN_ADJUST_PRIVILEGES, &t)) {
			if (LookupPrivilegeValue (NULL, SE_SHUTDOWN_NAME,
						  &l)) {
				TOKEN_PRIVILEGES p = {
					.PrivilegeCount = 1,
					.Privileges = {
						{
							.Luid = l,
							.Attributes =
							SE_PRIVILEGE_ENABLED
						}
					}
				};
				AdjustTokenPrivileges (t, FALSE, &p,
						       0, NULL, NULL);
			}