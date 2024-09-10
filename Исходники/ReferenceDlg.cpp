void CReferenceDlg::LoadBooks()
{
	int i,nMaxBooks;
	CString T;
	wchar_t c[5];
	CWnd* pWnd;
	CReferenceUtils ref;

	m_cboBook.ResetContent();   //clear contents of drop list box
	nMaxBooks=ref.GetMaxBook(m_nSourceText,m_pDoc);
	for (i=1;i<=nMaxBooks;i++)
	{
		T=ref.GetBookName(i, m_nSourceText,m_pDoc);
		m_cboBook.AddString(T);
	}
	m_ncboBook=m_nBook-1;    //initialize selected book
	CSpinButtonCtrl* pSpin=(CSpinButtonCtrl*) GetDlgItem(IDC_SPINCHAPTER);
	i=ref.GetMaxChapter(m_nBook, m_nSourceText); //get num of chapters in book
	pSpin->SetRange(1,i);   
	pSpin->SetPos(m_nChapter);         //select chapter
	_itow(m_nChapter,c,10);
	m_strChapter=c;
	pWnd=GetDlgItem(IDC_SPINCHAPTER);
	if (i==1) pWnd->EnableWindow(FALSE);    //if only one chapter in book, disable
	else pWnd->EnableWindow(TRUE);

	pSpin=(CSpinButtonCtrl*) GetDlgItem(IDC_SPINVERSE);
	i=ref.GetMaxVerse(m_nBook, m_nChapter, m_nSourceText, m_pDoc);   //get verses in this chapter
	pSpin->SetRange(1,i);     
	pSpin->SetPos(m_nVerse);  
	_itow(m_nVerse,c,10);
	m_strVerse=c;
	pWnd=GetDlgItem(IDC_SPINVERSE);
	if (i==1) pWnd->EnableWindow(FALSE);    //if only one chapter in book, disable
	else pWnd->EnableWindow(TRUE);
	UpdateData(FALSE);
}