int CNaviWnd::MouseTest(int x, int y)
{
	int res=0;
	CRect rect;
	CRgn rgn;
	for(int i=1;i<5;i++)
	{
		rect.SetRect(2+(i-1)*17,2,2+i*17,18);
		rgn.CreateRectRgnIndirect(&rect);
		if(rgn.PtInRegion(x,y))
			res=i;
		rgn.DeleteObject();
	}
	rect.SetRect(180,8,195,18);
	rgn.CreateRectRgnIndirect(&rect);
		if(rgn.PtInRegion(x,y))
			res=5;
	rect.SetRect(178,20,1985,40);
	rgn.DeleteObject();
	rgn.CreateRectRgnIndirect(&rect);
		if(rgn.PtInRegion(x,y))
			res=6;
	return res;
}