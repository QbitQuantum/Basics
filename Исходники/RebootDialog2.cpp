void CN50_Shutdown(){
	KernelIoControl(QC_IOCTL_POWER_DOWN_REQ, NULL, 0, NULL, 0, NULL);
	SetSystemPowerState(NULL, POWER_STATE_OFF, POWER_FORCE);
}