void CTyHMProxy::DrawDC_Bmp(CDC *pDC, CElecMapView *pView)
{
	float minx,miny,maxx,maxy;
	pView->GetFloatRect(&minx,&miny,&maxx,&maxy);
	if (!IntersectRect(minx,miny,maxx,maxy)) return;


	GetRect(&minx,&miny,&maxx,&maxy);
	CPoint pt1,pt2;
	pt1=pView->UPtoLP(minx,miny);
	pt2=pView->UPtoLP(maxx,maxy);
	CRect rt;
	rt.SetRect(pt1,pt2);
	rt.NormalizeRect();
  
	DrawImage(m_str1,pDC,pt1.x,pt1.y,rt.Width(),rt.Height(),m_bTranslate1,m_color1);

}