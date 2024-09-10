void getProcList(){
	for (int i=0; i<32; i++)
		wsprintf(procLIST[i].szName, L"");
	PROCESSENTRY32 pe32;
	DWORD dwPID=0;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPNOHEAPS | TH32CS_SNAPPROCESS, dwPID);
	if(hProcessSnap ==INVALID_HANDLE_VALUE)
		return;
	pe32.dwSize=sizeof(PROCESSENTRY32);
	if( !Process32First( hProcessSnap, &pe32 ) ){
		CloseToolhelp32Snapshot(hProcessSnap);
		return;
	}
	do{
		procLIST[iLISToffset].dwID=pe32.th32ProcessID;
		wsprintf(procLIST[iLISToffset++].szName, L"%s", pe32.szExeFile);
	} while( Process32Next( hProcessSnap, &pe32 ) );

	CloseToolhelp32Snapshot(hProcessSnap);

	//for (int i=0; i<32; i++){
	//	DEBUGMSG(1, (L"%i\t0x%08x\t'%s'\n", i, procLIST[i].dwID, procLIST[i].szName));
	//}
}