void CMiniCADDoc::OpenCrossBoardIni(LPCTSTR lpFilename)
{
	CMiniCADView* pView;
	POSITION pos=GetFirstViewPosition();
	pView=(CMiniCADView*)GetNextView(pos);
	//pView->m_GraphicsMode=Layout; 
//----------------------------------------------------------
	CDC* dc=pView->GetDC();
	int Xmilimeters=dc->GetDeviceCaps(HORZSIZE);
	int Ymilimeters=dc->GetDeviceCaps(VERTSIZE);
	int Xpixels=dc->GetDeviceCaps(HORZRES);
	int Ypixels=dc->GetDeviceCaps(VERTRES);
	//pView->ReleaseDC(dc);
	DeleteDC(dc->m_hDC);
//----------------------------------------------------------
	double mXPixel=(double)Xpixels/((double)Xmilimeters);
	double mYPixel=(double)Ypixels/((double)Ymilimeters);

	/*CADStyle* pStyle = new CADStyle();
	m_Graphics.m_Styles.Add(pStyle);
	strcpy(pStyle->m_Name,"样式1");
	strcpy(pStyle->m_Font,"SIMKAI.TTF");*/

	m_Graphics.m_BKColor=RGB(173,174,173);
	m_Graphics.m_WhiteColor=RGB(0,0,0); 
	m_Graphics.m_GraphicsMode=Layout;
	m_Graphics.m_bLineWidth=false; 
	m_Graphics.m_mXPixel=mXPixel;
	m_Graphics.m_mYPixel=mYPixel;
	m_Graphics.m_Unit=UNIT_MILLIMETER;
	m_Graphics.m_PaperOrient=HORIZONTAL;
//----------------------------------------------------------
	m_Graphics.m_Extmin.x = 0;
	m_Graphics.m_Extmin.y = 0;
	m_Graphics.m_Extmax.x = A3_WIDTH;
	m_Graphics.m_Extmax.y = A3_HEIGHT;

	m_Graphics.m_Bound.left=m_Graphics.m_Extmin.x*m_Graphics.m_mXPixel;
	m_Graphics.m_Bound.top=-m_Graphics.m_Extmax.y*m_Graphics.m_mYPixel;
	m_Graphics.m_Bound.right=m_Graphics.m_Bound.left+A3_WIDTH*m_Graphics.m_mXPixel;
	m_Graphics.m_Bound.bottom=m_Graphics.m_Bound.top+A3_HEIGHT*m_Graphics.m_mYPixel;
	m_Graphics.m_PaperLeft=m_Graphics.m_Extmin.x;
	m_Graphics.m_PaperTop=m_Graphics.m_Extmax.y;	
	m_Graphics.CreateDefault();

	CCrossBoardIniFile CrossBoardIniFile(&m_LayerGroup,&m_Graphics);
	CrossBoardIniFile.FileImport(lpFilename);

	CMainFrame*		m_pMain;
	m_pMain=(CMainFrame*) AfxGetApp()->m_pMainWnd;
	if(CrossBoardIniFile.m_nPaperCount == 1)
	{
		m_pMain->AddComboPaper("共 1 页",0);
	}
	else
	{
		CString str;
		for (int i=0; i<CrossBoardIniFile.m_nPaperCount; i++)
		{
			str.Format("第 %d 页",i+1);
			m_pMain->AddComboPaper(str,i+1);
		}
	}
	if (CrossBoardIniFile.m_nPaperCount > 0)
		m_pMain->SetComboSel(0);
//----------------------------------------------------------
	m_Graphics.CalZoomRate();
	m_Graphics.m_OriginZoomRate = m_Graphics.m_ZoomRate;
	m_Graphics.DrawGraphics(pView->m_pDisplay->GetDC()); 
	pView->Invalidate(false);
}