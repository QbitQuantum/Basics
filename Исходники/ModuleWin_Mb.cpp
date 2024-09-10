static bool ScanForHardwareChanges()
{
	DEVINST     devInst;
	CONFIGRET   status;
	//
	// Get the root devnode.
	//
	status = CM_Locate_DevNode(&devInst, NULL, CM_LOCATE_DEVNODE_NORMAL);
	if (status != CR_SUCCESS) {
		runtime_error("CM_Locate_DevNode failed.");
		return false;

	}

	status = CM_Reenumerate_DevNode(devInst, 0);
	if (status != CR_SUCCESS) {
		runtime_error("CM_Reenumerate_DevNode failed.");
		return false;
	}

	return true;
}