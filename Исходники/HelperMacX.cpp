OSType HelperMacX::getProcessSignature(pid_t pid){
	OSErr err;
	ProcessSerialNumber processSerialNumber;
	ProcessInfoRec processInfoRec;
	processInfoRec.processInfoLength = sizeof(processInfoRec);
	processInfoRec.processAppSpec = NULL;
	processInfoRec.processName = NULL;
	err = GetProcessForPID(pid, &processSerialNumber);
	if (noErr != err) {
		qWarning("HelperMacX::getProcessSignature: GetProcessForPID error for pid %d: %d", pid, err);
		return 0;
	}
	err = GetProcessInformation(&processSerialNumber, &processInfoRec);
	if (noErr != err) {
		qWarning("HelperMacX::getProcessSignature: GetProcessInformation error for pid %d: %d\n", pid, err);
		return 0;
	}
	return processInfoRec.processSignature;
}