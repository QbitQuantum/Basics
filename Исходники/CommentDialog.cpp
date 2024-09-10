void CCommentDialog::Localize(void)
{
	GetDlgItem(IDC_RESET)->SetWindowText(GetResString(IDS_PW_RESET));

	GetDlgItem(IDC_CMT_LQUEST)->SetWindowText(GetResString(IDS_CMT_QUEST));
	GetDlgItem(IDC_CMT_LAIDE)->SetWindowText(GetResString(IDS_CMT_AIDE));

	GetDlgItem(IDC_RATEQUEST)->SetWindowText(GetResString(IDS_CMT_RATEQUEST));
	GetDlgItem(IDC_RATEHELP)->SetWindowText(GetResString(IDS_CMT_RATEHELP));

	GetDlgItem(IDC_USERCOMMENTS)->SetWindowText(GetResString(IDS_COMMENT));
	GetDlgItem(IDC_SEARCHKAD)->SetWindowText(GetResString(IDS_SEARCHKAD));

	CImageList iml;
	iml.Create(16,16,theApp.m_iDfltImageListColorFlags|ILC_MASK,0,1);
	iml.SetBkColor(CLR_NONE);
	iml.Add(CTempIconLoader(_T("Rating_NotRated"), 16, 16));
	iml.Add(CTempIconLoader(_T("Rating_Fake"), 16, 16));
	iml.Add(CTempIconLoader(_T("Rating_Poor"), 16, 16));
	iml.Add(CTempIconLoader(_T("Rating_Fair"), 16, 16));
	iml.Add(CTempIconLoader(_T("Rating_Good"), 16, 16));
	iml.Add(CTempIconLoader(_T("Rating_Excellent"), 16, 16));
	m_ratebox.SetImageList(&iml);
	m_imlRating.DeleteImageList();
	m_imlRating.Attach(iml.Detach());
	
	m_ratebox.ResetContent();
	m_ratebox.AddItem(GetResString(IDS_CMT_NOTRATED), 0);
	m_ratebox.AddItem(GetResString(IDS_CMT_FAKE), 1);
	m_ratebox.AddItem(GetResString(IDS_CMT_POOR), 2);
	m_ratebox.AddItem(GetResString(IDS_CMT_FAIR), 3);
	m_ratebox.AddItem(GetResString(IDS_CMT_GOOD), 4);
	m_ratebox.AddItem(GetResString(IDS_CMT_EXCELLENT), 5);
	UpdateHorzExtent(m_ratebox, 16); // adjust dropped width to ensure all strings are fully visible

	RefreshData();
}