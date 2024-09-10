int CUpdateBase::GetUDisk(char pDiskName[], int len)
{
	DWORD	MaxDriveSet;
	DWORD	drive;
	TCHAR	szDrvName[33];
	int		count = 0;

	MaxDriveSet = GetLogicalDrives();//GetLogicalDrives

	for (drive = 0; drive < 32; drive++)  
	{
		if ( MaxDriveSet & (1 << drive) )  
		{
			DWORD temp = 1<<drive;
			_stprintf(szDrvName, _T("%c:\\"), 'A'+drive);//szDrvName
			
			if(GetDriveType(szDrvName)== DRIVE_REMOVABLE && (drive > 1))
			{
				pDiskName[count++] = 'A'+ (char)drive;
				if(count >= len)
				{
					break;
				}
			}
		}
	}

	return count;
}