//画地图
void CRadarMapCtrl::DrawMap()
{
	if(!m_map_bkgrdMap.bReady)
		return;
	CRect rect;
	GetClientRect(&rect);
	
	CDC * pDC=GetDC();
	//得到画布
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* oldbitmap=(CBitmap*)memDC.SelectObject(bmp);
	
	//先把m_dcmemory的拷贝过来
	memDC.BitBlt(0,0,rect.Width(),rect.Height(),&m_dcMemory,0,0,SRCCOPY);
	
	int cnt=(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle)/m_map_angleDelta + 1;
	CPoint points[1440];
	points[0].x=m_width/2;
	points[0].y=m_height/2;
	//内部解析角度
	double m_angleResolution=((double)(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle))/(m_map_bkgrdMap.mapDataLength-1);
	
	int j=1;
	for(int i=0;i<m_map_bkgrdMap.mapDataLength;i+=m_map_angleDelta)
	{
		int showPx=(int)(m_map_bkgrdMap.data[i]*m_map_scale/1000);
		
		if(showPx>m_map_totalPx)
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),(int)((double)(m_map_totalPx/m_map_scale) * 1000));
		}
		else
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),m_map_bkgrdMap.data[i]);
		}
		//DrawPoint(i,m_map_bkgrdMap.data[i]);
		//DrawLine(points[0],points[j]);
		j++;	
	}
	
	CPen   penBlue(PS_SOLID,   1,   RGB(50,200,255));   //蓝色
	CPen*   pOldPen   =   memDC.SelectObject(&penBlue);       
	
	CBrush   brushRed(RGB(0,  50,   200)); //蓝色
	CBrush*   pOldBrush   =   memDC.SelectObject(&brushRed);   	
	
	memDC.Polygon(points,j);
	
	memDC.SelectObject(pOldPen);   
	memDC.SelectObject(pOldBrush);   
	
	///////////////半透明
	BLENDFUNCTION bm;
	bm.BlendOp=AC_SRC_OVER;
	bm.BlendFlags=0;
	bm.SourceConstantAlpha=230;//0--255, 0是完全透明
	bm.AlphaFormat=0;  
	AlphaBlend(m_dcMemory.m_hDC,0,0,rect.Width(),rect.Height(),memDC.m_hDC,0,0,rect.Width(),rect.Height(),bm); 
	
	////////////////////////////////////////////////////////以下是正常画图
	/*
	if(!m_map_bkgrdMap.bReady)
	return;
	
	  int cnt=(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle)/m_map_angleDelta + 1;
	  CPoint points[1440];
	  points[0].x=m_width/2;
	  points[0].y=m_height/2;
	  //内部解析角度
	  double m_angleResolution=((double)(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle))/(m_map_bkgrdMap.mapDataLength-1);
	
	int j=1;
	for(int i=0;i<m_map_bkgrdMap.mapDataLength;i+=m_map_angleDelta)
	{
		int showPx=(int)(m_map_bkgrdMap.data[i]*m_map_scale/1000);
		
		if(showPx>m_map_totalPx)
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),(int)((double)(m_map_totalPx/m_map_scale) * 1000));
		}
		else
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),m_map_bkgrdMap.data[i]);
		}
		//DrawPoint(i,m_map_bkgrdMap.data[i]);
		//DrawLine(points[0],points[j]);
		j++;	
	}

	//CPen   penBlue(PS_SOLID,   1,   RGB(255,0,0));	//默认
	//CPen   penBlue(PS_SOLID,   1,   RGB(100,255,0));   //绿色
	CPen   penBlue(PS_SOLID,   1,   RGB(50,200,255));   //蓝色
	CPen*   pOldPen   =   m_dcMemory.SelectObject(&penBlue);       
	
	//CBrush   brushRed(RGB(123,  122,   23)); //默认
	//CBrush   brushRed(RGB(60,  200,   0)); //绿色
	CBrush   brushRed(RGB(0,  50,   200)); //蓝色
	CBrush*   pOldBrush   =   m_dcMemory.SelectObject(&brushRed);   	
	
	m_dcMemory.Polygon(points,j);

	//m_dcMemory.SelectObject(pOldPen);   
	//m_dcMemory.SelectObject(pOldBrush); 
*/
}