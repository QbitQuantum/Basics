bool VDUIJobControlDialog::OnLoaded() {
	VDSetDialogDefaultIcons(mhdlg);

	mStandardCaption = VDGetWindowTextW32(mhdlg);

	static const char *const szColumnNames[]={ "Name","Source","Dest","Start","End","Status" };
	HWND hwndItem = GetDlgItem(mhdlg, IDC_JOBS);
	for (int i=0; i<6; i++) {
		LV_COLUMN lvc;
		lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvc.fmt = LVCFMT_LEFT;
		lvc.cx = 1;
		lvc.pszText = (LPSTR)szColumnNames[i];

		ListView_InsertColumn(hwndItem, i, &lvc);
	}

	static const float kRelativeColumnWidths[]={ 50,100,100,50,50,100 };
	VDUISetListViewColumnsW32(hwndItem, kRelativeColumnWidths, 6);

	mResizer.Init(mhdlg);
	mResizer.Add(IDOK,				VDDialogResizerW32::kTR);
	mResizer.Add(IDC_MOVE_UP,		VDDialogResizerW32::kTR);
	mResizer.Add(IDC_MOVE_DOWN,		VDDialogResizerW32::kTR);
	mResizer.Add(IDC_POSTPONE,		VDDialogResizerW32::kTR);
	mResizer.Add(IDC_DELETE,		VDDialogResizerW32::kTR);
	mResizer.Add(IDC_START,			VDDialogResizerW32::kTR);
	mResizer.Add(IDC_ABORT,			VDDialogResizerW32::kTR);
	mResizer.Add(IDC_RELOAD,		VDDialogResizerW32::kTR);
	mResizer.Add(IDC_AUTOSTART,		VDDialogResizerW32::kTR);
	mResizer.Add(IDC_JOBS,			VDDialogResizerW32::kMC);
	mResizer.Add(IDC_CURRENTJOB,	VDDialogResizerW32::kBL);
	mResizer.Add(IDC_PROGRESS,		VDDialogResizerW32::kBC);
	mResizer.Add(IDC_PERCENT,		VDDialogResizerW32::kBR);

	GetWindowRect(mhdlg, &rInitial);
	VDUIRestoreWindowPlacementW32(mhdlg, "Job control", SW_SHOWNORMAL);
	VDUIRestoreListViewColumnsW32(hwndItem, "Job control: Columns");

	fUpdateDisable = false;

	ListView_SetExtendedListViewStyleEx(hwndItem, LVS_EX_FULLROWSELECT , LVS_EX_FULLROWSELECT);

	RECT rLV;
	GetClientRect(hwndItem, &rLV);

	OnJobQueueReloaded();
	OnJobQueueStatusChanged(g_VDJobQueue.GetQueueStatus());

	CheckButton(IDC_AUTOSTART, g_VDJobQueue.IsAutoRunEnabled());

	SendDlgItemMessage(mhdlg, IDC_PROGRESS, PBM_SETRANGE, 0, MAKELPARAM(0, 16384));

	if (g_dubber || g_VDJobQueue.IsRunInProgress()) {
		EnableControl(IDC_PROGRESS, false);
		EnableControl(IDC_PERCENT, false);
	} else {
		EnableControl(IDC_PROGRESS, true);
		EnableControl(IDC_PERCENT, true);
	}

	g_hwndJobs = mhdlg;

	g_VDJobQueue.SetCallback(this);

	return VDDialogFrameW32::OnLoaded();
}