BOOL FE_DialogConvert::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_outfilevalue=m_Doutfilename1;
	m_imagetypevalue=m_Doutputimagetype1;
    if (m_Doutputimagequality1<=33)
        m_qualityvalue=0;
    else if (m_Doutputimagequality1<=66)
        m_qualityvalue=1;
    else if (m_Doutputimagequality1>66)
        m_qualityvalue=2;

    m_inputimagetype=m_Dinputimagetype;
	_ultoa(m_Dinputimagesize,m_inputimagesize.GetBuffer(255),10);
	m_inputimagesize.ReleaseBuffer();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}