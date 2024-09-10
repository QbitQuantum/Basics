/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgTestBaseSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  тз╢клМ╪с╤НмБ╣дЁУй╪╩╞
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// йТптрЁхщфВ

	m_oTabTestBaseInstrument.m_pSiteData = m_pSiteData;	// ожЁ║йЩ╬щ
	m_oTabTestBaseInstrument.m_uiAim = 1;	// ╡Бйт╤тоС 1-ргфВё╩2-╪Л╡╗фВ
	m_oTabTestBaseInstrument.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// йТптрЁ╡Бйт╩Ы╠╬иХжцё╛ргфВ

	m_oTabTestBaseSensor.m_pSiteData = m_pSiteData;	// ожЁ║йЩ╬щ
	m_oTabTestBaseSensor.m_uiAim = 2;	// ╡Бйт╤тоС 1-ргфВё╩2-╪Л╡╗фВ
	m_oTabTestBaseSensor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);	// йТптрЁ╡Бйт╩Ы╠╬иХжцё╛╪Л╡╗фВ

	m_oTabTestLimitInstrument.m_pSiteData = m_pSiteData;	// ожЁ║йЩ╬щ
	m_oTabTestLimitInstrument.m_uiAim = 1;	// ╡Бйт╤тоС 1-ргфВё╩2-╪Л╡╗фВ
	m_oTabTestLimitInstrument.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 3);	// йТптрЁ╡Бйтеп╬щиХжцё╛ргфВ

	m_oTabTestLimitSensor.m_pSiteData = m_pSiteData;	// ожЁ║йЩ╬щ
	m_oTabTestLimitSensor.m_uiAim = 2;	// ╡Бйт╤тоС 1-ргфВё╩2-╪Л╡╗фВ
	m_oTabTestLimitSensor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 4);	// йТптрЁ╡Бйтеп╬щиХжцё╛╪Л╡╗фВ

	m_oTabWnd.AddTab(&m_oTabTestBaseInstrument, "    Instrument Base    ");	// йТптрЁ╡Бйт╩Ы╠╬иХжцё╛ргфВ
	m_oTabWnd.AddTab(&m_oTabTestBaseSensor, "    Sensor Base    ");	// йТптрЁ╡Бйт╩Ы╠╬иХжцё╛╪Л╡╗фВ
	m_oTabWnd.AddTab(&m_oTabTestLimitInstrument, "    Instrument Limit    ");	// йТптрЁ╡Бйтеп╬щиХжцё╛ргфВ
	m_oTabWnd.AddTab(&m_oTabTestLimitSensor, "    Sensor Limit    ");	// йТптрЁ╡Бйтеп╬щиХжцё╛╪Л╡╗фВ

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);

	m_oTabTestBaseInstrument.OnBnClickedButtonReset();
	m_oTabTestBaseSensor.OnBnClickedButtonReset();
	m_oTabTestLimitInstrument.OnBnClickedButtonReset();
	m_oTabTestLimitSensor.OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// рЛЁё: OCX йТптрЁс╕╥╣╩ь FALSE
}