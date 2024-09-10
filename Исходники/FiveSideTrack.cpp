/*
*--------------------------------------------------------------------------------
*  函数名	: CreatePos
*  功能		: 计算出轨迹上所有点的集合，保存到列表中去
*  算法		: 由五角星的外部五个顶点和内部五个顶点依次连线，
*		      能过 LineDDA 函数得出所有的轨迹点座标
*  前置条件 : 必须已经设定了轨迹起始点座标和终止点座标
*  后置条件 : 在 m_listTrackPoints 列表中保存所有轨迹点的座标
*--------------------------------------------------------------------------------
*/
BOOL CFiveSideTrack::CreatePos()
{
	CPoint ptOutVertex[5];

	// 五等分圆，得到五个顶点座标
	SplitCircle(m_ptTrackStartPoint, m_ptTrackEndPoint, 5, ptOutVertex);

	// 将五边形的外部五顶点依次连线用 LineDDA 得到轨迹点
	LineDDA(ptOutVertex[0].x, ptOutVertex[0].y, ptOutVertex[1].x, ptOutVertex[1].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[1].x, ptOutVertex[1].y, ptOutVertex[2].x, ptOutVertex[2].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[2].x, ptOutVertex[2].y, ptOutVertex[3].x, ptOutVertex[3].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[3].x, ptOutVertex[3].y, ptOutVertex[4].x, ptOutVertex[4].y, CTrack::AddPosToList, (LPARAM) this);
	LineDDA(ptOutVertex[4].x, ptOutVertex[4].y, ptOutVertex[0].x, ptOutVertex[0].y, CTrack::AddPosToList, (LPARAM) this);

	return TRUE;
}