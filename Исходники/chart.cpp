void CChart::PrintChart(CDC *pDC,int x , int y)
{
	
	int xPixel ;
	int yPixel  ;
	int oldmapmode ;

	CDC *dc = GetDC();
	
	xPixel = pDC->GetDeviceCaps(LOGPIXELSX);
	yPixel = pDC->GetDeviceCaps(LOGPIXELSY);
	
	//Calculate ratio to be zoomed.
	xPixel =  xPixel /dc->GetDeviceCaps(LOGPIXELSX);
	yPixel =  yPixel /dc->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(dc);
	
	oldmapmode = pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(xPixel,yPixel);
	pDC->SetViewportOrg(x,y);

	DrawBorder(pDC);
	pDC->DrawEdge(m_ctlRect,BDR_SUNKENINNER|BDR_SUNKENOUTER, BF_RECT);
	DrawChartTitle(pDC);
	if ( bLogScale )
	   DrawLogGrid(pDC);
	DrawGrid(pDC);
	
	DrawAxis(pDC) ;
	DrawGridLabel(pDC);
	Plot(pDC) ;

	pDC->SetMapMode(oldmapmode);
}