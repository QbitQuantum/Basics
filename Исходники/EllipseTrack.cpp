/*
*--------------------------------------------------------------------------------
*  函数名: CreatePos
*  功能	 : 计算出椭圆轨迹上所有点的集合，保存到列表中去
*  算法  : 根据椭圆方程求椭圆上的每一个点
*  前置条件: 必须已经设定了轨迹起始点座标和终止点座标
*  后置条件: 在 m_listTrackPoints 列表中保存所有轨迹点的座标
*--------------------------------------------------------------------------------
*/
BOOL CEllipseTrack::CreatePos()
{
	if (m_ptTrackStartPoint.y == m_ptTrackEndPoint.y && m_ptTrackStartPoint.x == m_ptTrackEndPoint.x)
	{
		// 水平线或是垂直线
		LineDDA(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y, m_ptTrackEndPoint.x, m_ptTrackEndPoint.y, CTrack::AddPosToList, (LPARAM) this);
	}
	else
	{
		int xCenter, yCenter;
		double a, b;
		
		xCenter = (m_ptTrackEndPoint.x + m_ptTrackStartPoint.x) / 2;
		yCenter = (m_ptTrackEndPoint.y + m_ptTrackStartPoint.y) / 2;
		
		// 椭圆 X 轴长度
		a = abs(m_ptTrackEndPoint.x - m_ptTrackStartPoint.x) / 2;
		// 椭圆 Y 轴长度
		b = abs(m_ptTrackEndPoint.y - m_ptTrackStartPoint.y) / 2;
				
		double b2 = b * b;
		double a2 = a * a;
	
		// 中心点为(xCenter, yCenter)，扫描 X 轴求 Y 值
		int x, y;		
		for (x = (int) -a; x <= (int) a; x++)
		{
			y = (int) sqrt(b2 - (b2 / a2) * (x * x));
			AddPoint(x + xCenter, y + yCenter);
		}
		// 求对称轴，求两次是为了让坐标是连贯的
		for (x = (int) -a; x <= (int) a; x++)
		{
			y = (int) sqrt(b2 - (b2 / a2) * (x * x));
			AddPoint(x + xCenter, yCenter - y);
		}


		// 中心点为(xCenter, yCenter)，扫描 Y 轴求 X 值
		for (y = (int) b; y >= (int) -b; y--)
		{
			x = (int) sqrt(a2 - (a2 / b2) * (y * y));
			if ( y != (int) sqrt(b2 - (b2 / a2) * (x * x)) )
			{
				AddPoint(xCenter - x, yCenter + y);
			}
		}
		// 求对称轴，求两次是为了让坐标是连贯的
		for (y = (int) -b; y <= (int) b; y++)
		{
			x = (int) sqrt(a2 - (a2 / b2) * (y * y));
			if ( y != (int) sqrt(b2 - (b2 / a2) * (x * x)) )
			{
				AddPoint(x + xCenter, y + yCenter);
			}
		}
	}

	return TRUE;
}