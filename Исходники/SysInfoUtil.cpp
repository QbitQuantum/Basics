CString GetHddDriveInfo()
{
	int index=0;
	float fTotalSize=0;
	HANDLE hDevice;
	CString Result;
	CString HardDisk;
	DWORD junk;
	DISK_GEOMETRY pdg;
	BOOL bWin9X = FALSE;
	if (GetVersion() >= 0x80000000) {
		bWin9X = TRUE;
	}

	HardDisk.Format("\\\\.\\PhysicalDrive%d",index);

	hDevice=CreateFile(HardDisk,0,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);

	if (hDevice==INVALID_HANDLE_VALUE)
		Result=="Error: Can not Query Hard Disk Drives.";

	while (hDevice!=INVALID_HANDLE_VALUE)
	{
		BOOL bResult=DeviceIoControl(hDevice,IOCTL_DISK_GET_DRIVE_GEOMETRY,
									NULL,0,
									&pdg,sizeof(DISK_GEOMETRY),
									&junk,
									(LPOVERLAPPED) NULL);
		if (bResult)
		{
			CString Temp;
			Temp.Format("Hard Disk Drive %d : ",index+1);
			Result+=Temp;

			double DiskSize=pdg.Cylinders.QuadPart * pdg.TracksPerCylinder * 
				pdg.SectorsPerTrack * pdg.BytesPerSector/1024/1024/1024.0;
			
			Temp.Format("%.2f GB\n", DiskSize);
			Result+=Temp;
//			fTotalSize += atof(Temp);
		}

		CloseHandle(hDevice);

		index++;
		HardDisk.Format("\\\\.\\PhysicalDrive%d",index);
		hDevice=CreateFile(HardDisk,0,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	}

	double dTotalSize = 0, dTotalFree = 0;
	ULARGE_INTEGER AvailableToCaller, Disk, Free;
	for (int iCounter=0; iCounter < MAX_OF_HARD_DISKS; iCounter++)
	{
		if (GetDriveType(HardDiskLetters[iCounter])==DRIVE_FIXED)
		{
			if (GetDiskFreeSpaceEx(HardDiskLetters[iCounter],&AvailableToCaller,&Disk,&Free))
			{
				CString Temp;
//				Temp.Format("*** Hard Disk: (%s) ***\r\n",HardDiskLetters[iCounter]);
//				Result+=Temp;

//				Temp.Format("Total size: %I64d (MB)\r\n",Disk.QuadPart/1024/1024);
//				Result+=Temp;

//				ULONGLONG Used=Disk.QuadPart-Free.QuadPart;
//				Temp.Format("Used: %I64d (MB)\r\n",Used/1024/1024);
//				Result+=Temp;

//				Temp.Format("Free: %I64d (MB)\r\n\r\n",Free.QuadPart/1024/1024);
//				Result+=Temp;

				dTotalSize += (INT64)(Disk.QuadPart);
				dTotalFree += (INT64)(Free.QuadPart);

				if (bWin9X) {
					Temp.Format("Hard Disk Drive %d : %.2f GB\n", iCounter+1, dTotalSize/1024/1024/1024.0);
					Result += Temp;
				}
			}
		}
	}

	dTotalSize = dTotalSize/1024/1024/1024.0;
	dTotalFree = dTotalFree/1024/1024/1024.0;

//	CString Temp;
//	Temp.Format("Number of Hard Disk Drives: %d\n",index);
	CString strTotalSize, strTotalFree;
	strTotalSize.Format("%.2f Gigabytes Usable Hard Drive Capacity\n", dTotalSize/*fTotalSize*/);
	strTotalFree.Format("%.2f Gigabytes Hard Drive Free Space\n", dTotalFree);
	Result=strTotalSize+strTotalFree+Result;

	return Result + "\n";
}