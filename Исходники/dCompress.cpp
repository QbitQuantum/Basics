void dCompress::OnShowWindow(BOOL bShow, UINT nStatus)
{
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), true);
	CDialog::OnShowWindow(bShow, nStatus);

	//cPriority.SetCurSel(2);
	DWORD prio[] = {HIGH_PRIORITY_CLASS, ABOVE_NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, BELOW_NORMAL_PRIORITY_CLASS, IDLE_PRIORITY_CLASS};
	HANDLE hProc = GetCurrentProcess();

	DWORD cPrio = GetPriorityClass(hProc);
	for(int i=0;i<sizeof(prio)/sizeof(prio[0]);i++){
		if(cPrio == prio[i]){
			cPriority.SetCurSel(i);
			break;
		}
	}
}