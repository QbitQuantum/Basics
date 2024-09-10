void CUnspecifiedCharacter::OnPaintCellDatatblcharacter(short Pane, long Row, long Column, long* Status)
{
	if (Row!=dtHeadingsRow && Column!=dtLabelsColumn)
	{
		float left, top, right, bottom;
		COLORREF lColor;
		CString R,A,C,T;
		CSize Sz;
		COleVariant var;
		CBrush* brush;
		CFont* pFont;
		CFont* pCurrentFont;
		CDC* pDC;

		CDTCell cell=m_datatblCharacter.GetCellSet().GetItem(Row,Column);
		cell.GetRect(Pane, &left, &top, &right, &bottom);
		CRect rect=CRect((int) left, (int) top, (int) right, (int) bottom);
		pDC=m_datatblCharacter.GetDC();
		R=m_strCharacter;
		lColor=m_datatblCharacter.GetBackColor();
		brush=new CBrush(lColor);  //get a blue brush
		pDC->FillRect(rect,brush);
		delete brush;
		pCurrentFont=pDC->GetCurrentFont();           //save the current font
		pFont=pDC->SelectObject(&m_fontTarget);    //select the target language's font
		pDC->ExtTextOut((int)left+2,(int)top+2,ETO_CLIPPED,rect,R,NULL);
		pDC->SelectObject(pCurrentFont);
		m_datatblCharacter.ReleaseDC(pDC);
		*Status=1L;
	}
}