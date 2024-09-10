void get_disk_info_all(){
    DWORD dwNumBytesForDriveStrings;
    char DriveStrings[255];
    char* dp = DriveStrings;
    
    dwNumBytesForDriveStrings = GetLogicalDriveStrings(254,dp);
    if (dwNumBytesForDriveStrings != 0) {
	/* GetLogicalDriveStringsIs supported on this platform */
	while (*dp != 0) {
	    output_drive_info(dp);
	    dp = strchr(dp,0) +1;
	}
    }
    else {
	/* GetLogicalDriveStrings is not supported (some old W95) */
	DWORD dwDriveMask = GetLogicalDrives();
	int nDriveNum;
	char drivename[]="A:\\";
	/*printf("DriveName95 DriveType BytesAvail BytesTotal BytesTotalFree\n");*/
	for (nDriveNum = 0; dwDriveMask != 0;nDriveNum++) {
	    if (dwDriveMask & 1) {
		drivename[0]='A'+ nDriveNum;
		output_drive_info(drivename);
	    }
	    dwDriveMask = dwDriveMask >> 1;
	}
    }
}