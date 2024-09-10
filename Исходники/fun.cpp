void ProcessList()
{
	// 1. ListBox 초기화(비워주기)
	SendMessage(hMainList, LVM_DELETEALLITEMS, 0, 0);

	// 2. Process 리스트 나열  
	HANDLE	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);
	if( hSnap == 0 )
		return ;

	PROCESSENTRY32 ppe;
	BOOL	b     = Process32First(hSnap, &ppe);
	while( b )
	{
		int i=0;
		// ListBox Ctrl에 데이터 추가 
		ListBoxAddData(i, ppe);

		b = Process32Next(hSnap, &ppe);
	}
	SetWindowText(hStaticLog, "프로세스 리스트를 초기화 하였습니다.");

	CloseHandle(hSnap);
}