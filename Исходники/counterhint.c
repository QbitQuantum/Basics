LRESULT
CounterHintOnInitDialog(
	IN HWND hWnd,
	IN UINT uMsg,
	IN WPARAM wp,
	IN LPARAM lp
	)
{
	HWND hWndBar;
    PDIALOG_OBJECT Object;
	WCHAR Buffer[MAX_PATH];
	PCOUNTERHINT_CONTEXT Context;

	hWndBar = GetDlgItem(hWnd, IDC_PROGRESS);
	SendMessage(hWndBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
	SendMessage(hWndBar, PBM_SETSTEP, 10, 0); 
	
	SetWindowText(hWnd, L"D Probe");

    Object = (PDIALOG_OBJECT)SdkGetObject(hWnd);
	Context = (PCOUNTERHINT_CONTEXT)Object->Context;
	Context->NumberToScan = MspGetRecordCount(Context->DtlObject);
	Context->ScannedNumber = 0;

	QueueUserWorkItem(CounterScanWorkItem, Context, 
		              WT_EXECUTEDEFAULT|WT_EXECUTELONGFUNCTION);

	StringCchPrintf(Buffer, MAX_PATH, L"Scanning %u records ...", 
		            Context->NumberToScan);

	SetDlgItemText(hWnd, IDC_STATIC, Buffer);
	
    SetTimer(hWnd, 1, 1000, NULL);
	SdkCenterWindow(hWnd);
	return 0;
}