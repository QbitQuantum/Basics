void CPhoneticFeaturesDlg::OnPaintCellDatatblctrlphoneticfeatures(short Pane, long Row, long Column, long* Status)
{
	if (Row!=dtHeadingsRow && (Column==0 || (m_nType==2 && Column==1)))  //if phonetic features, paint just column 1; if capital letters, paint columns 1 and 2
	{
		float left, top, right, bottom;
		COLORREF lColor;
		CString R,S,A,C,T,strSequence,strIgnoredCharacters;
		CSize Sz;
		COleVariant var;
		CBrush* brush;
		CFont* pFont;
		CFont* pCurrentFont;
		CDC* pDC;
		CDTCell cell;

		if (Column==0) R=m_pDoc->m_starCharacters[Row+1];  //+1 to skip over space character
		else R=m_pDoc->m_starCharacterCapitals[Row+1];
		cell=m_datatblPhoneticFeatures.GetCellSet().GetItem(Row,Column);
		cell.GetRect(Pane, &left, &top, &right, &bottom);
		CRect rect=CRect((int) left, (int) top, (int) right, (int) bottom);
		pDC=m_datatblPhoneticFeatures.GetDC();
//		R=GetStringFromTargetLexicon(m_nSyntacticCategory,Row,0);  //get a root
//		R=L"abc";
		lColor=m_datatblPhoneticFeatures.GetBackColor();
		brush=new CBrush(lColor);  //get a blue brush
		pDC->FillRect(rect,brush);
		delete brush;
		pCurrentFont=pDC->GetCurrentFont();           //save the current font
		pFont=pDC->SelectObject(&m_fontTarget);    //select the target language's font
		pDC->ExtTextOut((int)left+2,(int)top+2,ETO_CLIPPED,rect,R,NULL);
		pDC->SelectObject(pCurrentFont);
		m_datatblPhoneticFeatures.ReleaseDC(pDC);
		*Status=1L;
	}
}