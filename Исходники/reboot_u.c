static int reboot(int flags) {
#ifdef _WIN32_WCE
	if(flags != RB_AUTOBOOT) {
		errno = EINVAL;
		return -1;
	}
#ifdef _USE_KIOCTL
	if(!KernelIoControl(IOCTL_HAL_REBOOT, NULL, 0, NULL, 0, NULL)) return -1;
#else
	unsigned long int e = SetSystemPowerState(NULL, POWER_STATE_RESET, 0);
	if(e) {
		SetLastError(e);
		return -1;
	}
#endif
#else
	if(enable_shutdown_privilege() < 0) return -1;
#ifdef _WIN32_WNT_NATIVE
	SHUTDOWN_ACTION action;
	switch(flags) {
		case RB_AUTOBOOT:
			action = ShutdownReboot;
			break;
		case RB_HALT_SYSTEM:
			action = ShutdownNoReboot;
			break;
		default:
			errno = EINVAL;
			return -1;
	}
	long int status = NtShutdownSystem(action);
	if(status < 0) {
		__set_errno_from_ntstatus(status);
		return -1;
	}
#else
#ifdef _USE_EWX
	unsigned int wflags = EWX_FORCE;
	switch(flags) {
		case RB_AUTOBOOT:
			flags |= EWX_REBOOT;
			break;
		case RB_HALT_SYSTEM:
			flags |= EWX_SHUTDOWN;
			break;
		default:
			errno = EINVAL;
			return -1;
	}
	if(!ExitWindowsEx(wflags, 0)) {
		__set_errno_from_oserror();
		return -1;
	}
#else
	if(!InitiateSystemShutdownW(NULL, NULL, 0, 1, flags & EWX_REBOOT)) {
		__set_errno_from_oserror();
		return -1;
	}
#endif
#endif		/* _WIN32_WNT_NATIVE */
#endif		/* _WIN32_WCE */
	while(1) sleep(10000);
}