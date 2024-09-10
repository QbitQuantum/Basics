BOOL CPPageAccelTbl::OnApply()
{
	AfxGetMyApp()->UnregisterHotkeys();
	UpdateData();

	AppSettings& s = AfxGetAppSettings();

	s.wmcmds.RemoveAll();
	s.wmcmds.AddTail(&m_wmcmds);

	CAtlArray<ACCEL> pAccel;
	pAccel.SetCount(m_wmcmds.GetCount());
	POSITION pos = m_wmcmds.GetHeadPosition();
	for (int i = 0; pos; i++) {
		pAccel[i] = m_wmcmds.GetNext(pos);
	}
	if (s.hAccel) {
		DestroyAcceleratorTable(s.hAccel);
	}
	s.hAccel = CreateAcceleratorTable(pAccel.GetData(), pAccel.GetCount());

	GetParentFrame()->m_hAccelTable = s.hAccel;

	s.fWinLirc = !!m_fWinLirc;
	s.strWinLircAddr = m_WinLircAddr;
	if (s.fWinLirc) {
		s.WinLircClient.Connect(m_WinLircAddr);
	}
	s.fUIce = !!m_fUIce;
	s.strUIceAddr = m_UIceAddr;
	if (s.fUIce) {
		s.UIceClient.Connect(m_UIceAddr);
	}
	s.fGlobalMedia = !!m_fGlobalMedia;

	AfxGetMyApp()->RegisterHotkeys();

	s.AccelTblColWidth.bEnable = true;
	s.AccelTblColWidth.cmd		= m_list.GetColumnWidth(COL_CMD);
	s.AccelTblColWidth.key		= m_list.GetColumnWidth(COL_KEY);
	s.AccelTblColWidth.id		= m_list.GetColumnWidth(COL_ID);
	s.AccelTblColWidth.mwnd		= m_list.GetColumnWidth(COL_MOUSE);
	s.AccelTblColWidth.mfs		= m_list.GetColumnWidth(COL_MOUSE_FS);
	s.AccelTblColWidth.appcmd	= m_list.GetColumnWidth(COL_APPCMD);
	s.AccelTblColWidth.remcmd	= m_list.GetColumnWidth(COL_RMCMD);
	s.AccelTblColWidth.repcnt	= m_list.GetColumnWidth(COL_RMREPCNT);

	return __super::OnApply();
}