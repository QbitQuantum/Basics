bool CMPCVideoDecSettingsWnd::OnActivate()
{
	DWORD	dwStyle = WS_VISIBLE|WS_CHILD|WS_BORDER;
	int		nPosY	= 10;
	GUID*	DxvaGui = NULL;

#if defined(REGISTER_FILTER) | INCLUDE_MPC_VIDEO_DECODER
	m_grpFFMpeg.Create (ResStr (IDS_VDF_FFSETTINGS), WS_VISIBLE|WS_CHILD | BS_GROUPBOX, CRect (10,  nPosY, 330, nPosY+150), this, IDC_STATIC);

	#if defined(REGISTER_FILTER) | INTERNAL_DECODER_H264
	// Decoding threads
	nPosY += VERTICAL_SPACING;
	m_txtThreadNumber.Create (ResStr (IDS_VDF_THREADNUMBER), WS_VISIBLE|WS_CHILD, CRect (LEFT_SPACING,  nPosY, 190, nPosY+15), this, IDC_STATIC);
	m_cbThreadNumber.Create  (WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL, CRect (200,  nPosY-4, 260, nPosY+90), this, IDC_PP_THREAD_NUMBER);
	m_cbThreadNumber.AddString (_T("1"));
	m_cbThreadNumber.AddString (_T("2"));
	m_cbThreadNumber.AddString (_T("3"));
	m_cbThreadNumber.AddString (_T("4"));
	m_cbThreadNumber.AddString (_T("5"));
	m_cbThreadNumber.AddString (_T("6"));
	m_cbThreadNumber.AddString (_T("7"));
	m_cbThreadNumber.AddString (_T("8"));

	// H264 deblocking mode
	nPosY += VERTICAL_SPACING;
	m_txtDiscardMode.Create (ResStr (IDS_VDF_SKIPDEBLOCK), WS_VISIBLE|WS_CHILD, CRect (LEFT_SPACING,  nPosY, 190, nPosY+15), this, IDC_STATIC);
	m_cbDiscardMode.Create  (WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL, CRect (200,  nPosY-4, 315, nPosY+90), this, IDC_PP_DISCARD_MODE);
	m_cbDiscardMode.AddString (ResStr (IDS_VDF_DBLK_NONE));
	m_cbDiscardMode.AddString (ResStr (IDS_VDF_DBLK_DEFAULT));
	m_cbDiscardMode.AddString (ResStr (IDS_VDF_DBLK_NONREF));
	m_cbDiscardMode.AddString (ResStr (IDS_VDF_DBLK_BIDIR));
	m_cbDiscardMode.AddString (ResStr (IDS_VDF_DBLK_NONKFRM));
	m_cbDiscardMode.AddString (ResStr (IDS_VDF_DBLK_ALL));
	#endif
	
	// Error recognition
	nPosY += VERTICAL_SPACING;
	m_txtErrorRecognition.Create (ResStr (IDS_VDF_ERROR_RECOGNITION), WS_VISIBLE|WS_CHILD, CRect (LEFT_SPACING,  nPosY, 190, nPosY+15), this, IDC_STATIC);
	m_cbErrorRecognition.Create  (WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL, CRect (200,  nPosY-4, 315, nPosY+90), this, IDC_PP_DISCARD_MODE);
	m_cbErrorRecognition.AddString (ResStr (IDS_VDF_ERR_CAREFUL));
	m_cbErrorRecognition.AddString (ResStr (IDS_VDF_ERR_COMPLIANT));
	m_cbErrorRecognition.AddString (ResStr (IDS_VDF_ERR_AGGRESSIVE));
	m_cbErrorRecognition.AddString (ResStr (IDS_VDF_ERR_VERYAGGRESSIVE));

	// IDCT Algo
	nPosY += VERTICAL_SPACING;
	m_txtIDCTAlgo.Create (ResStr (IDS_VDF_IDCT_ALGO), WS_VISIBLE|WS_CHILD, CRect (LEFT_SPACING,  nPosY, 190, nPosY+15), this, IDC_STATIC);
	m_cbIDCTAlgo.Create  (WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL, CRect (200,  nPosY-4, 315, nPosY+90), this, IDC_PP_DISCARD_MODE);
	m_cbIDCTAlgo.AddString (ResStr (IDS_VDF_IDCT_AUTO));
	m_cbIDCTAlgo.AddString (ResStr (IDS_VDF_IDCT_LIBMPG2));
	m_cbIDCTAlgo.AddString (ResStr (IDS_VDF_IDCT_SIMPLE_MMX));
	m_cbIDCTAlgo.AddString (ResStr (IDS_VDF_IDCT_XVID));
	m_cbIDCTAlgo.AddString (ResStr (IDS_VDF_IDCT_SIMPLE));

	nPosY += VERTICAL_SPACING;
	m_cbARMode.Create (ResStr (IDS_VDF_AR_MODE), WS_VISIBLE|WS_CHILD|BS_AUTOCHECKBOX|BS_LEFTTEXT, CRect (LEFT_SPACING,  nPosY, 315, nPosY+15), this, IDC_PP_AR);
	m_cbARMode.SetCheck(FALSE);

	nPosY = 170;
#endif

	m_grpDXVA.Create   (ResStr (IDS_VDF_DXVA_SETTING),   WS_VISIBLE|WS_CHILD | BS_GROUPBOX, CRect (10, nPosY, 330, nPosY+110), this, IDC_STATIC);

	// DXVA mode
	nPosY += VERTICAL_SPACING;
	m_txtDXVAMode.Create (ResStr (IDS_VDF_DXVA_MODE), WS_VISIBLE|WS_CHILD, CRect (LEFT_SPACING,  nPosY, 120, nPosY+15), this, IDC_STATIC);
	m_edtDXVAMode.Create (WS_CHILD|WS_VISIBLE|WS_DISABLED, CRect (120,  nPosY, 315, nPosY+20), this, 0);

	// Video card description
	nPosY += VERTICAL_SPACING;
	m_txtVideoCardDescription.Create (ResStr (IDS_VDF_VIDEOCARD), WS_VISIBLE|WS_CHILD, CRect (LEFT_SPACING,  nPosY, 120, nPosY+15), this, IDC_STATIC);
	m_edtVideoCardDescription.Create (WS_CHILD|WS_VISIBLE|WS_DISABLED, CRect (120,  nPosY, 315, nPosY+20), this, 0);
	m_edtVideoCardDescription.SetWindowText (m_pMDF->GetVideoCardDescription());
	
	
	DxvaGui = m_pMDF->GetDXVADecoderGuid();
	if (DxvaGui != NULL)
	{
		CString DXVAMode = GetDXVAMode (DxvaGui);
		m_edtDXVAMode.SetWindowText (/*GetDXVAMode (DxvaGui)*/DXVAMode);
	}
	else
	{
		m_txtDXVAMode.ShowWindow (SW_HIDE);
		m_edtDXVAMode.ShowWindow (SW_HIDE);
	}

	for(CWnd* pWnd = GetWindow(GW_CHILD); pWnd; pWnd = pWnd->GetNextWindow())
		pWnd->SetFont(&m_font, FALSE);

	#if defined(REGISTER_FILTER) | INCLUDE_MPC_VIDEO_DECODER
	if (m_pMDF)
	{
		#if defined(REGISTER_FILTER) | INTERNAL_DECODER_H264
		m_cbThreadNumber.SetCurSel		(m_pMDF->GetThreadNumber() - 1);
		m_cbDiscardMode.SetCurSel		(FindDiscardIndex (m_pMDF->GetDiscardMode()));
		#endif
		m_cbErrorRecognition.SetCurSel	(m_pMDF->GetErrorRecognition()-1);
		m_cbIDCTAlgo.SetCurSel			(m_pMDF->GetIDCTAlgo());

		m_cbARMode.SetCheck(m_pMDF->GetARMode());
	}
	#endif

	return true;
}