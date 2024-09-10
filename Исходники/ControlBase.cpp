// 鼠标移动事件处理
BOOL CControlBase::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_bIsVisible || !m_bRresponse) return false;
	
	// 保存原始的鼠标位置,并进行位置变换
	CPoint oldPoint = point;
	OnMousePointChange(point);

	BOOL bRresponse = false;
	if(m_pControl)
	{
		CPoint pt = point;
		// 如果是控件内置滚动条子控件,则不进行位置变换,因为滚动条位置是不需要变换的
		UINT uControlID = m_pControl->GetControlID();
		if((SCROLL_V == uControlID) || (SCROLL_H == uControlID))
		{
			pt = oldPoint;
		}
		if((m_pControl->PtInRect(pt) && m_pControl->OnCheckMouseResponse(nFlags, pt)) || m_bMouseDown)
		{
			if(m_pControl->OnMouseMove(nFlags, pt))
			{
				return true;
			}
			return false;
		}
	}

	CControlBase * pOldControl = m_pControl;
	m_pControl =  NULL;

	if(!m_strTooltip.IsEmpty() && PtInRect(point) && OnCheckMouseResponse(nFlags, point))
	{
		// 如果当前控件有Tooltip,并且当前Tooltip设置的是其他控件,则设置Tooltip
		if(GetTooltipCtrlID() != GetID())
		{
			SetTooltip(this, m_strTooltip, m_rc, FALSE, m_nTipWidth);
			SetTooltipCtrlID(GetID());
		}
	}

	// 调用控件的设置鼠标光标函数
	OnControlSetCursor(nFlags, point);

	// 调用控件的鼠标移动函数
	bRresponse = OnControlMouseMove(nFlags, point);

	// 发送鼠标移动的DUI消息
	if(m_bDuiMsgMouseMove)
	{
		if(PtInRect(point))
		{
			// 发送鼠标在控件范围内移动的消息
			SendMessage(MSG_MOUSE_MOVE, (WPARAM)nFlags, (LPARAM)(&point));
			m_bMouseLeave = FALSE;
		}else
		{
			if(!m_bMouseLeave)
			{
				// 发送鼠标离开控件的消息(离开之后仅发送一次离开消息)
				SendMessage(MSG_MOUSE_LEAVE, (WPARAM)nFlags, (LPARAM)(&point));
				m_bMouseLeave = TRUE;
			}
		}
	}

	if(!m_bMouseDown)
	{
		for (size_t i = 0; i < m_vecControl.size(); i++)
		{
			CControlBase * pControlBase = m_vecControl.at(i);
			if (pControlBase)
			{
				CPoint pt = point;
				// 如果是控件内置滚动条子控件,则不进行位置变换,因为滚动条位置是不需要变换的
				UINT uControlID = pControlBase->GetControlID();
				if((SCROLL_V == uControlID) || (SCROLL_H == uControlID))
				{
					pt = oldPoint;
				}
				if(pControlBase->OnMouseMove(nFlags, pt))
				{
					if(pControlBase->PtInRect(pt))
					{
						m_pControl = pControlBase;
					}
					bRresponse = true;
				}
			}
		}


		if (pOldControl)
		{
			bRresponse = true;
		}

		if (m_pControl)
		{
			bRresponse = true;
		}
	}

	return bRresponse;
}