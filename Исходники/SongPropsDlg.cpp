BOOL CSongPropsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(theApp.LoadIcon(IDR_MAINFRAME), 0);

	CPatchGeneralDlg::InitNoteCombo(m_KeySig);
	m_KeySig.SetCurSel(m_Props.m_Key);
	m_TimeSigNumer.SetVal(m_Props.m_Meter.m_Numerator);
	CStringArrayEx	sUnit;
	CPartBassDlg::GetPowerOfTwoStrings(sUnit, 
		CSong::CMeter::MIN_UNIT_EXP, CSong::CMeter::MAX_UNIT_EXP);
	int	nUnits = sUnit.GetSize();
	for (int iUnit = 0; iUnit < nUnits; iUnit++)
		m_TimeSigDenom.AddString(sUnit[iUnit]);
	DWORD	iSelUnit;
	_BitScanReverse(&iSelUnit, m_Props.m_Meter.m_Denominator);
	m_TimeSigDenom.SetCurSel(iSelUnit);
	m_Tempo.SetVal(m_Props.m_Tempo);
	m_Transpose.SetVal(m_Props.m_Transpose);
	m_Comments.SetWindowText(m_Props.m_Comments);

	EnableToolTips();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}