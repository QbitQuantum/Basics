//virtual override since we can have different fonts for different columns
CFont* CWListCtrl::getFontForSubItem(int nItem, int nCol)
{
	static CFont fntNotEditable;

#ifndef hab218
				// it'd sure be nice if there were an easier
				// way...
	ASSERT(getParent());
	CWListView *pParent = getParent();
	CWList * pList;
	if (pParent->IsKindOf(RUNTIME_CLASS(CDlgManualParseChoice)))
	  {
		CDlgManualParseChoice * pDlg = (CDlgManualParseChoice *)pParent;
		pList = pDlg->m_pList;
	  }
	else
	  {
		pList = pParent->m_pList;
	  }
	ASSERT(pList);
	if(pList->getUseLangFontInColumn(nCol))
	  {
		CFont* pF;
		if (pParent->IsKindOf(RUNTIME_CLASS(CDlgManualParseChoice)))
		  {
		CDlgManualParseChoice * pDlg = (CDlgManualParseChoice *)pParent;
		pF = pDlg->getLangFont();
		  }
		else
		  pF = pParent->getLangFont();
		ASSERT(pF);
		return pF;
	  }
#else // hab218
	ASSERT(getParent());
	ASSERT(getParent()->m_pList);
	if(getParent()->m_pList->getUseLangFontInColumn(nCol))
	{
		CFont* pF = getParent()->getLangFont();
		ASSERT(pF);
		return pF;
	}
#endif //hab218
		// if not editable
/*	else if(! (getParent()->m_pList->m_dwEditableColumns & (1 << nCol)))
	{
		//fntNotEditable.FromHandle((HFONT)GetStockObject(ANSI_FIXED_FONT));
		if(!HFONT(fntNotEditable))
		{
			CFont* pf = GetFont();
			LOGFONT lf;
			pf->GetLogFont(&lf);
			lf.lfItalic=TRUE;
			fntNotEditable.CreateFontIndirect(&lf);
			//fntNotEditable.CreateFont(lf.lfHeight ,0,0,0,0,TRUE,0,0,ANSI_CHARSET,0,0,0,lf.lfPitchAndFamily ,lf.lfFaceName);
		}
		return &fntNotEditable;
		//return getParent()->getLangFont();
	}
*/	else
		return GetFont();

}