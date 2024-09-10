int listProcesses_matchFirst(char *strToMatch)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

	PROCESSENTRY32 pe32;
	memset(&pe32,0,sizeof(pe32));
	pe32.dwSize = sizeof(pe32);

	int bCont = Process32First(hSnap,&pe32);
	while(bCont == TRUE)
	{
		if (strToMatch != NULL && pe32.szExeFile != NULL)
		{
			if(strstr(pe32.szExeFile,strToMatch) != NULL)
			{
				printf(" %04x : %s\n",pe32.th32ProcessID,pe32.szExeFile );
				return pe32.th32ProcessID;
			}
		}
		bCont = Process32Next(hSnap,&pe32);
	}
	return 0;
}