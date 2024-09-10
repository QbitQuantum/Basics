/*
 * Get interface info, which contains Adapter[] that has the MIB index
 */
PIP_INTERFACE_INFO getIpInterfaceInfo(void) {

	DWORD size = 0;
	PIP_INTERFACE_INFO  info = NULL;

	// Get the require size of the structure
	if (GetInterfaceInfo(info, &size) == ERROR_INSUFFICIENT_BUFFER) {
		info = (PIP_INTERFACE_INFO) malloc(size);
	} else {
		return NULL;
	}

	// Now fill in the structure
	GetInterfaceInfo(info, &size);

	return info;
}