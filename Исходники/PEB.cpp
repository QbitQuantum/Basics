PEB64 PEBUtils::GetProcessPEB64(LPWSTR &procName)
{    
	hProcess = OpenProcess(procName);
	if(CheckProcess(hProcess))
	{
		printf("Remote Process is 32 bit but using GetProcesPeb64\n");
		exit(EXIT_FAILURE);
	}
    status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(PROCESS_BASIC_INFORMATION), &dwLength);
    
    if(status != 0x0)
    {
        printf("NtQueryInformationProcess Error  0x%x\n", status);
		exit(EXIT_FAILURE);
    }
    
    printf("PEB address : 0x%x\n", pbi.PebBaseAddress);

    SIZE_T dwBytesRead = 0x0;
	ReadPEB64(dwBytesRead);

    return peb64;
}