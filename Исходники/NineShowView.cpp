BOOL CNineShowView::InitGridContent(CNineGridCtrl *pGrid )  
{
	m_nCols=4;
    m_nFixRows=1;
	m_nFixCols=0;
    m_nRows=20;  


	try {
 		pGrid->SetRowCount(m_nRows);
		pGrid->SetColumnCount(m_nCols);
		pGrid->SetFixedRowCount(m_nFixRows);
		pGrid->SetFixedColumnCount(m_nFixCols);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
   	pGrid->SetGridColor(m_pDoc->m_colorArray[18],m_pDoc->m_colorArray[17],m_pDoc->m_colorArray[16]);

//20000615
    pGrid->SetFixedBkColor(m_pDoc->m_colorArray[18]);
//20000615


	CFont Font;
	LOGFONT m_lf;
	memset(&m_lf,0,sizeof(LOGFONT));
	m_lf.lfHeight = -12;
	m_lf.lfWidth=0;
	m_lf.lfWeight=400;
	m_lf.lfCharSet=134;
	strcpy(m_lf.lfFaceName,"宋体");

	Font.CreateFontIndirect(&m_lf);

	pGrid->SetFont(&Font);
	Font.DeleteObject();
 	return TRUE;
}