/*
*--------------------------------------------------------------------------------
*  函数名	: CreatePos
*  功能		: 计算出轨迹上所有点的集合，保存到列表中去
*  参数		: VOID
*  算法		: 通过 LineDDA 函数得出所有的轨迹点座标
*  前置条件 : 必须已经设定了轨迹起始点座标和终止点座标
*  后置条件 : 在 m_listTrackPoints 列表中保存所有轨迹点的座标
*--------------------------------------------------------------------------------
*/
BOOL CRectangleTrack::CreatePos()
{
	if (m_ptTrackStartPoint.y == m_ptTrackEndPoint.y && m_ptTrackStartPoint.x == m_ptTrackEndPoint.x)
	{
		// 水平线或是垂直线
		LineDDA(m_ptTrackStartPoint.x, m_ptTrackStartPoint.y, m_ptTrackEndPoint.x, m_ptTrackEndPoint.y, CTrack::AddPosToList, (LPARAM) this);
	}
	else
	{
		CPoint ptVertex[4];
		
		ptVertex[0] = m_ptTrackStartPoint;
		ptVertex[1].x = m_ptTrackEndPoint.x;
		ptVertex[1].y = m_ptTrackStartPoint.y;
		ptVertex[2] = m_ptTrackEndPoint;
		ptVertex[3].x = m_ptTrackStartPoint.x;
		ptVertex[3].y = m_ptTrackEndPoint.y;
				
		// 将矩形的四个顶点依次连线用 LineDDA 得到轨迹点
		LineDDA(ptVertex[0].x, ptVertex[0].y, ptVertex[1].x, ptVertex[1].y, CTrack::AddPosToList, (LPARAM) this);
		LineDDA(ptVertex[1].x, ptVertex[1].y, ptVertex[2].x, ptVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
		LineDDA(ptVertex[2].x, ptVertex[2].y, ptVertex[3].x, ptVertex[3].y, CTrack::AddPosToList, (LPARAM) this);
		LineDDA(ptVertex[3].x, ptVertex[3].y, ptVertex[0].x, ptVertex[0].y, CTrack::AddPosToList, (LPARAM) this);
	}
	return TRUE;
}