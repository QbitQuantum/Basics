//////////////////////////////////////////////////////////////////
//功能: 移动对象
//////////////////////////////////////////////////////////////////
void CFormObj::MoveTo(const CRectF &position, BOOL bUniformScale, CLayoutView* pView)
{
	ASSERT_VALID(this);

	if (m_bUniformScale)
		bUniformScale = TRUE;

	CRectF rcObj;
	Invalidate(pView);

	float fScaleX = position.Width() / m_position.Width();
	float fScaleY = position.Height() / m_position.Height();

	if (bUniformScale)
	{
		if (ABSOLUTEVALUE(fScaleX) < ABSOLUTEVALUE(fScaleY))
			fScaleX = fScaleX >= 0 ? ABSOLUTEVALUE(fScaleY) : -ABSOLUTEVALUE(fScaleY);
		else
			fScaleY = fScaleY >= 0 ? ABSOLUTEVALUE(fScaleX) : -ABSOLUTEVALUE(fScaleX);
	}

	CDevObjList* pObjects = m_pFormDoc->GetObjects();
	POSITION posObj = pObjects->GetHeadPosition();
	CDevObj* pObj;
	while (posObj != NULL)
	{
		pObj = pObjects->GetNext(posObj);
		rcObj = pObj->GetPositionRect();
		rcObj.OffsetRect(-m_position.TopLeft());
		rcObj.left = rcObj.left * fScaleX;
		rcObj.right = rcObj.right * fScaleX;
		rcObj.top = rcObj.top * fScaleY;
		rcObj.bottom = rcObj.bottom * fScaleY;
		rcObj.OffsetRect(position.TopLeft());
		pObj->MoveTo(rcObj, bUniformScale, pView);
	}
	
	m_ptRotateBase.x = position.left + (m_ptRotateBase.x - m_position.left) * fScaleX;
	m_ptRotateBase.y = position.top + (m_ptRotateBase.y - m_position.top) * fScaleY;

	m_position = position;
//	m_position.NormalizeRect();
	RecalcPosition();
	m_pFormDoc->SetDocSize(0, 0, TRUE);
		
	Invalidate(pView);
}