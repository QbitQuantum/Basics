bool CMpaDecSettingsWnd::OnActivate()
{
	DWORD dwStyle = WS_VISIBLE|WS_CHILD|WS_TABSTOP;

	CRect r;

	CPoint p(10, 10);

	m_outputformat_static.Create(ResStr(IDS_MPADECSETTINGSWND_0), dwStyle, CRect(p, CSize(120, m_fontheight)), this);

	p.y += m_fontheight + 5;

	m_outputformat_combo.Create(dwStyle|CBS_DROPDOWNLIST, CRect(p + CSize(10, 0), CSize(100, 200)), this, IDC_PP_COMBO1);
	m_outputformat_combo.SetItemData(m_outputformat_combo.AddString(_T("PCM 16 Bit")), SF_PCM16);
	m_outputformat_combo.SetItemData(m_outputformat_combo.AddString(_T("PCM 24 Bit")), SF_PCM24);
	m_outputformat_combo.SetItemData(m_outputformat_combo.AddString(_T("PCM 32 Bit")), SF_PCM32);
	m_outputformat_combo.SetItemData(m_outputformat_combo.AddString(_T("IEEE Float")), SF_FLOAT32);
	m_outputformat_combo.SetCurSel(0);

	for(int i = 0; i < m_outputformat_combo.GetCount(); i++)
		if((int)m_outputformat_combo.GetItemData(i) == m_outputformat)
			m_outputformat_combo.SetCurSel(i);

	p.y += 30;

	CString	strSpeak;
	strSpeak.Format (_T("%s%s"), ResStr(IDS_MPADECSETTINGSWND_1), GetDolbyMode(m_ddmode));
	m_ac3spkcfg_static.Create(ResStr(IDS_MPADECSETTINGSWND_1) + GetDolbyMode(m_ddmode), dwStyle, CRect(p, CSize(220, m_fontheight)), this);

	p.y += m_fontheight + 5;

	m_ac3spkcfg_combo.Create(dwStyle|CBS_DROPDOWNLIST, CRect(p + CSize(150, 0), CSize(100, 200)), this, IDC_PP_COMBO2);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(_T("单声道")), A52_MONO);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(_T("双单声道")), A52_CHANNEL);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(_T("立体声")), A52_STEREO);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(_T("杜比立体声")), A52_DOLBY);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_3F)), A52_3F);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_2F_1R)), A52_2F1R);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_3F_1R)), A52_3F1R);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_2F_2R)), A52_2F2R);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_3F_2R)), A52_3F2R);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_CHANNEL_1)), A52_CHANNEL1);
	m_ac3spkcfg_combo.SetItemData(m_ac3spkcfg_combo.AddString(ResStr(IDS_MPA_CHANNEL_2)), A52_CHANNEL2);

	for(int i = 0, sel = abs(m_ac3spkcfg) & A52_CHANNEL_MASK; i < m_ac3spkcfg_combo.GetCount(); i++)
		if((int)m_ac3spkcfg_combo.GetItemData(i) == sel)
			m_ac3spkcfg_combo.SetCurSel(i);

	m_ac3spkcfg_combo.GetWindowRect(r);
	ScreenToClient(r);

	m_ac3lfe_check.Create(_T("LFE"), dwStyle|BS_AUTOCHECKBOX, CRect(CPoint(r.left, r.bottom + 3), CSize(50, m_fontheight)), this, IDC_PP_CHECK4);
	m_ac3lfe_check.SetCheck(!!(abs(m_ac3spkcfg) & A52_LFE));

	for(int i = 0, h = max(20, m_fontheight)+1; i < countof(m_ac3spkcfg_radio); i++, p.y += h)
	{
		static const TCHAR* labels[] = {m_strDecodeToSpeaker, _T("SPDIF")};
		DWORD ddwStyle = dwStyle;
		if(wcscmp(labels[i],_T("SPDIF")) == 0){
			ddwStyle =  (dwStyle& ~WS_VISIBLE);
		}
		m_ac3spkcfg_radio[i].Create(labels[i],ddwStyle|BS_AUTORADIOBUTTON|(i == 0 ? WS_GROUP : 0), CRect(p + CPoint(10, 0), CSize(140, h)), this, IDC_PP_RADIO1+i);
	}

	CheckRadioButton(IDC_PP_RADIO1, IDC_PP_RADIO2, m_ac3spkcfg >= 0 ? IDC_PP_RADIO1 : IDC_PP_RADIO2);

	p.y += 5;

	m_ac3spkcfg_check.Create(ResStr(IDS_MPA_DYNRANGE), dwStyle|BS_AUTOCHECKBOX, CRect(p + CPoint(10, 0), CSize(150, m_fontheight)), this, IDC_PP_CHECK1);
	m_ac3spkcfg_check.SetCheck(m_ac3drc);

	p.y += m_fontheight + 10;

	m_dtsspkcfg_static.Create(ResStr(IDS_MPADECSETTINGSWND_7), dwStyle, CRect(p, CSize(120, m_fontheight)), this);

	p.y += m_fontheight + 5;

	m_dtsspkcfg_combo.Create(dwStyle|CBS_DROPDOWNLIST, CRect(p + CSize(150, 0), CSize(100, 200)), this, IDC_PP_COMBO3);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(_T("单声道")), DTS_MONO);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(_T("双单声道")), DTS_CHANNEL);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(_T("立体声")), DTS_STEREO);
	//m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(_T("Stereo ..")), DTS_STEREO_SUMDIFF);
	//m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(_T("Stereo ..")), DTS_STEREO_TOTAL);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(ResStr(IDS_MPA_3F)), DTS_3F);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(ResStr(IDS_MPA_2F_1R)), DTS_2F1R);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(ResStr(IDS_MPA_3F_1R)), DTS_3F1R);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(ResStr(IDS_MPA_2F_2R)), DTS_2F2R);
	m_dtsspkcfg_combo.SetItemData(m_dtsspkcfg_combo.AddString(ResStr(IDS_MPA_3F_2R)), DTS_3F2R);

	for(int i = 0, sel = abs(m_dtsspkcfg) & DTS_CHANNEL_MASK; i < m_dtsspkcfg_combo.GetCount(); i++)
		if((int)m_dtsspkcfg_combo.GetItemData(i) == sel)
			m_dtsspkcfg_combo.SetCurSel(i);

	m_dtsspkcfg_combo.GetWindowRect(r);
	ScreenToClient(r);

	m_dtslfe_check.Create(_T("LFE"), dwStyle|BS_AUTOCHECKBOX, CRect(CPoint(r.left, r.bottom + 3), CSize(50, m_fontheight)), this, IDC_PP_CHECK5);
	m_dtslfe_check.SetCheck(!!(abs(m_dtsspkcfg) & DTS_LFE));

	for(int i = 0, h = max(20, m_fontheight)+1; i < countof(m_dtsspkcfg_radio); i++, p.y += h)
	{
		static const TCHAR* labels[] = {m_strDecodeToSpeaker, _T("SPDIF")};
		DWORD ddwStyle = dwStyle;
		if(wcscmp(labels[i],_T("SPDIF")) == 0){
			ddwStyle =  (dwStyle& ~WS_VISIBLE);
		}
		m_dtsspkcfg_radio[i].Create(labels[i], ddwStyle|BS_AUTORADIOBUTTON|(i == 0 ? WS_GROUP : 0), CRect(p + CPoint(10, 0), CSize(140, h)), this, IDC_PP_RADIO3+i);
	}

	CheckRadioButton(IDC_PP_RADIO3, IDC_PP_RADIO4, m_dtsspkcfg >= 0 ? IDC_PP_RADIO3 : IDC_PP_RADIO4);

	p.y += 5;

	m_dtsspkcfg_check.Create(ResStr(IDS_MPA_DYNRANGE), dwStyle|WS_DISABLED|BS_AUTOCHECKBOX, CRect(p + CPoint(10, 0), CSize(150, m_fontheight)), this, IDC_PP_CHECK2);
	m_dtsspkcfg_check.SetCheck(m_dtsdrc);

	p.y += m_fontheight + 10;

	m_aacspkcfg_static.Create(ResStr(IDS_MPADECSETTINGSWND_11), dwStyle, CRect(p, CSize(120, m_fontheight)), this);

	p.y += m_fontheight + 5;

	m_aacdownmix_check.Create(ResStr(IDS_MPADECSETTINGSWND_12), dwStyle|BS_AUTOCHECKBOX, CRect(p + CPoint(10, 0), CSize(150, m_fontheight)), this, IDC_PP_CHECK3);
	m_aacdownmix_check.SetCheck(m_aacdownmix);

	for(CWnd* pWnd = GetWindow(GW_CHILD); pWnd; pWnd = pWnd->GetNextWindow())
		pWnd->SetFont(&m_font, FALSE);

	return true;
}