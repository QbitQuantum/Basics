//鼠标消息
VOID CSkinSplitter::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags,Point);

	if (m_bMouseDown==true)
	{
		//获取位置
		CRect rcWindow;
		GetWindowRect(&rcWindow);

		//效验位置
		CPoint PointParent=Point;
		MapWindowPoints(GetParent(),&PointParent,1);

		//控件位置
		CSize SizeControl;
		SizeControl.SetSize(rcWindow.Width(),rcWindow.Height());

		//设置光标
		if (m_SplitterType==SplitterType_Hor)
		{
			if ((PointParent.y>(m_nMaxDragPos-SizeControl.cy/2))||(PointParent.y<(m_nMinDragPos+SizeControl.cy/2)))
			{
				//设置光标
				SetCursor(LoadCursor(NULL,IDC_NO));

				//设置位置
				PointParent.y=__min(m_nMaxDragPos-SizeControl.cy/2,PointParent.y);
				PointParent.y=__max(m_nMinDragPos+SizeControl.cy/2,PointParent.y);
			}
			else SetCursor(LoadCursor(NULL,IDC_SIZENS));
		}
		else
		{
			if ((PointParent.x>(m_nMaxDragPos-SizeControl.cx/2))||(PointParent.x<(m_nMinDragPos+SizeControl.cx/2)))
			{
				//设置光标
				SetCursor(LoadCursor(NULL,IDC_NO));

				//设置位置
				PointParent.x=__min(m_nMaxDragPos-SizeControl.cx/2,PointParent.x);
				PointParent.x=__max(m_nMinDragPos+SizeControl.cx/2,PointParent.x);
			}
			else SetCursor(LoadCursor(NULL,IDC_SIZEWE));
		}

		//转换位置
		CPoint PointScreen=PointParent;
		GetParent()->ClientToScreen(&PointScreen);
		
		//计算区域
		CRect rcCurrentDraw=m_rcDrawLine;
		if (m_SplitterType==SplitterType_Hor)
		{
			rcCurrentDraw.top=PointScreen.y-SizeControl.cy/2;
			rcCurrentDraw.bottom=rcCurrentDraw.top+SizeControl.cy;
		}
		else
		{
			rcCurrentDraw.left=PointScreen.x-SizeControl.cx/2;
			rcCurrentDraw.right=rcCurrentDraw.left+SizeControl.cx;
		}
		
		//绘画线条
		if (rcCurrentDraw!=m_rcDrawLine)
		{
			//设置 DC
			CDC * pDC=CDC::FromHandle(::GetDC(NULL));
			pDC->SelectObject(CDC::GetHalftoneBrush());

			//绘画拆分
			pDC->PatBlt(m_rcDrawLine.left,m_rcDrawLine.top,m_rcDrawLine.Width(),m_rcDrawLine.Height(),PATINVERT);
			pDC->PatBlt(rcCurrentDraw.left,rcCurrentDraw.top,rcCurrentDraw.Width(),rcCurrentDraw.Height(),PATINVERT);

			//释放资源
			::ReleaseDC(NULL,pDC->m_hDC);

			//设置变量
			m_rcDrawLine=rcCurrentDraw;
		}
	}

	return;
}