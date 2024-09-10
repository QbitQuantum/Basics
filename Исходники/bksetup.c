////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Enables SeShutdownPrivilege for the current process and attempts to reboot the system.
//
VOID Reboot(VOID)
{
	BOOL OldValue;

	if (NT_SUCCESS(RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, (PBOOLEAN)&OldValue)))
		ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}