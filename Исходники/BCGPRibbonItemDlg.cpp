BOOL CBCGPRibbonItemDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout ();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor (IDC_BCGBARRES_IMAGE_LIST, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth, CSize(0, 0), CSize(100, 100));
		pLayout->AddAnchor (IDD_BCGBAR_RES_LABEL1, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeNone, CSize(50, 100));
		pLayout->AddAnchor (IDC_BCGBARRES_NAME, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeHorz, CSize(50, 100), CSize(100, 100));
		pLayout->AddAnchor (IDOK, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone, CSize(100, 100));
		pLayout->AddAnchor (IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone, CSize(100, 100));
	}
	
	m_wndImageList.SetImages(&m_images);
	
	int nCount = m_images.GetCount ();

	for (int iImage = 0; iImage < nCount; iImage++)
	{
		CBCGPToolbarButton* pButton = new CBCGPToolbarButton;

		pButton->SetImage (iImage);

		m_wndImageList.AddButton (pButton);
		m_Buttons.AddTail (pButton);
	}

	m_wndImageList.SelectButton (m_iSelImage);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}