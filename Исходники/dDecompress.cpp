void dDecompress::OnCbnSelchangeCpriority()
{
	DWORD prio[] = {HIGH_PRIORITY_CLASS, ABOVE_NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS, BELOW_NORMAL_PRIORITY_CLASS, IDLE_PRIORITY_CLASS};
	HANDLE hProc = GetCurrentProcess();

	if(!SetPriorityClass(hProc, prio[cPriority.GetCurSel()])){
		DWORD cPrio = GetPriorityClass(hProc);
		for(int i=0;i<sizeof(prio)/sizeof(prio[0]);i++){
			if(cPrio == prio[i]){
				cPriority.SetCurSel(i);
				break;
			}
		}
		MessageBox(loadString(IDS_CANT_CHANGE_PRIORITY), "KGB Archiver");
	}
}