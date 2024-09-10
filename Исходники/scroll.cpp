// 消息响应
LRESULT CScrollV::OnMessage(UINT uID, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if(uID == BT_UP)
	{
		if(BUTTOM_UP == lParam)
		{
			CRect rcUpdate;
			rcUpdate.SetRectEmpty();
			MoveRange(-m_nRowRange);
		}
	}
	else if (uID == BT_DOWN)
	{
		if(BUTTOM_UP == lParam)
		{
			CRect rcUpdate;
			rcUpdate.SetRectEmpty();
			MoveRange(m_nRowRange);
		}
	}
	return 0L; 
}