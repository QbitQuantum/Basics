void readIniFile()
{
	char Buffer[128];
	char iniFilePath[MAX_PATH];
	GetCurrentDirectoryA(sizeof(iniFilePath), iniFilePath);
	lstrcatA(iniFilePath, "\\multidisk_speed.ini");

	IPC_getPrivateProfileString("Option", "DriveCnt", "1", Buffer, sizeof(Buffer), iniFilePath);
	driveCnt = atoi(Buffer);

	for (int i = 0; i < driveCnt; i++)
	{
		sprintf(Buffer, "DriveName%d", i);
		IPC_getPrivateProfileString("Option", Buffer, "\\\\.\\H:", driveName[i], sizeof(driveName[i]), iniFilePath);
	}

	IPC_getPrivateProfileString("Option", "DriveFlag", "0", Buffer, sizeof(Buffer), iniFilePath);
	drvFlg = atoi(Buffer);

	for (int i = 0; i < driveCnt; i++)
	{
		sprintf(Buffer, "FullFileName%d", i);
		IPC_getPrivateProfileString("Option", Buffer, "data.bin", fileName[i], sizeof(fileName[i]), iniFilePath);
	}

	IPC_getPrivateProfileString("Option", "BufferSizeInMb", "1", Buffer, sizeof(Buffer), iniFilePath);
	bBufSize = atoi(Buffer) * 1024 * 1024;
	IPC_getPrivateProfileString("Option", "BufferNum", "1", Buffer, sizeof(Buffer), iniFilePath);
	bufCnt = atoi(Buffer);
	IPC_getPrivateProfileString("Option", "BufferStatistic", "0", Buffer, sizeof(Buffer), iniFilePath);
	bufStat = atoi(Buffer);
}