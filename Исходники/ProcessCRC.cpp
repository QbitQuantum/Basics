bool __GetExeCRC(DWORD & r_dwProcCRC, DWORD & r_dwFileCRC)
{
	std::string exeFileName;
	LPCVOID c_pvBaseAddress;

	GetExcutedFileName(exeFileName);

	if (GetProcessInformation(exeFileName, &c_pvBaseAddress))
		r_dwProcCRC = GetProcessMemoryCRC(c_pvBaseAddress);
	else
		r_dwProcCRC = 0;

	r_dwFileCRC = GetFileCRC32(exeFileName.c_str());
	return true;
}