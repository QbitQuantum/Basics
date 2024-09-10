static XnStatus GetOSName(xnOSInfo* pOSInfo)
{
	if (IsWindows8Point1OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "Windows8Point1OrGreater\n");
	else if (IsWindows8OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "Windows8\n");
	else if (IsWindows7SP1OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "Windows7SP1\n");
	else if (IsWindows7OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "Windows7\n");
	else if (IsWindowsVistaSP2OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "VistaSP2\n");
	else if (IsWindowsVistaSP1OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "VistaSP1\n");
	else if (IsWindowsVistaOrGreater())
		sprintf(pOSInfo->csOSName, "%s", "Vista\n");
	else if (IsWindowsXPSP3OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "XPSP3\n");
	else if (IsWindowsXPSP2OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "XPSP2\n");
	else if (IsWindowsXPSP1OrGreater())
		sprintf(pOSInfo->csOSName, "%s", "XPSP1\n");
	else if (IsWindowsXPOrGreater())
		sprintf(pOSInfo->csOSName, "%s", "XP\n");
	else
		sprintf(pOSInfo->csOSName, "%s", "Unknown win version\n");

	return (XN_STATUS_OK);
}