static DWORD WINAPI Work(PVOID args){

	Times = GetTickCount();
	while(i++<1000000){
		
		SwitchToThread();
		
	}
	Total += GetTickCount() - Times;
	_tprintf(_T("1 000 000 Context Switch in diferent process  %.5f  ms\n"),Total/1000000);
	return 0;

}