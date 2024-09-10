UINT OnShowdireNum(LPVOID lParam)
{
  	int x=0;
	int y=0;
	int t=0;
   	double pi=3.1415926535898;
	double r=170;
    int a=0;
    int b=0;
	int m_shownum=0;
 	BITMAP  m_bitmapinfo;                                       //位图信息结构                  
	CBitmap m_bitmap;                                           //位图处理类  
	
	CDC  m_men;
	m_men.CreateCompatibleDC(m_diredashdc);

	CPen m_pen1(NULL,3,RGB(255,0,0));
	CPen m_pen2(NULL,5,RGB(255,0,0));
	
	CRect m_childrect;
	m_childrect.top=0;
	m_childrect.left=0;
    m_childrect.bottom=600;
    m_childrect.right=700;

	
	while(1){
    m_bitmap.LoadBitmapA(MAKEINTRESOURCEA(IDB_YAM));
    m_bitmap.GetBitmap(&m_bitmapinfo);
	m_men.SelectObject(&m_bitmap);
	
	m_shownum=(int)m_flightinfo.m_udirection; 
	
	m_men.SelectObject(&m_pen1);
	m_men.SelectStockObject(NULL_BRUSH);
	m_men.Ellipse(m_direrect.Width()/2-14-15+5+120,m_direrect.Height()/2+6-15-2+110,m_direrect.Width()/2-14+15+5+120,m_direrect.Height()/2+6+15-2+110);
	m_pen1.DeleteObject();
	
	m_men.SelectObject(&m_pen2);   
	m_men.Ellipse(m_direrect.Width()/2-14-5+5+120,m_direrect.Height()/2+6-5-2+110,m_direrect.Width()/2-14+5+5+120,m_direrect.Height()/2+6+5-2+110);
	m_pen2.DeleteObject();
	
	m_men.SelectObject(&m_pen1);
	m_men.MoveTo(m_direrect.Width()/2-14+5+120,m_direrect.Height()/2+6-2+110);
    x=m_direrect.Width()/2-14+5+120;
	y=m_direrect.Height()/2+6-2+110;
	t=(int)((m_shownum-1050)*180/900);
    a=x-(int)(r*cos(t*pi/180));
	b=y-(int)(r*sin(t*pi/180));
	m_men.LineTo(a,b);
	m_pen1.DeleteObject();

	m_diredashdc->SetStretchBltMode(HALFTONE);
    m_diredashdc->StretchBlt(m_direrect.top,m_direrect.left,m_direrect.Width(),m_direrect.Height(),&m_men,0,0,m_bitmapinfo.bmWidth,m_bitmapinfo.bmHeight,SRCCOPY);

	m_bitmap.DeleteObject();


	Sleep(14);
	}
	
	DeleteDC(m_men.m_hDC);
    
	return 1;
}