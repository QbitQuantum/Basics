void COthelloView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	COthelloDoc *pDoc=GetDocument();
	if (m_Current>=0 && (pDoc->m_MainTable).GetTable(m_Current)<1)
	{
		if (m_CurPlay==T_BLACK && (pDoc->m_MainTable).IsDown(m_CurCol,m_CurRow,T_BLACK))
		{
			BiltBitmap(m_CurX,m_CurY,m_CurX+33,m_CurY+33,m_hBlack);
			(pDoc->m_MainTable).SetTable(m_Current,T_BLACK);
			DrawTable(m_CurCol,m_CurRow,T_BLACK);
			if (!(pDoc->m_MainTable).HaveDown(T_WHITE))
			{
				if (!(pDoc->m_MainTable).HaveDown(T_BLACK))
				{
					pDoc->GameOver();
				}
				else
				{
					MessageBox("White Pass!!!");
					m_CurPlay=T_BLACK;
				}
			}
			else
			{
				::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
				SetCursor(m_hcurWhite);
cont:
				CPoint point,pos;
				point=pDoc->TryIt(T_WHITE,T_DEPTH);
				(pDoc->m_MainTable).SetTable(point.x,point.y,T_WHITE);
				pos=GetPosition(point.x,point.y);
				//MessageBeep(MB_ICONINFORMATION);
				BiltBitmap(pos.x,pos.y,pos.x+33,pos.y+33,m_hWhite);
				Sleep(100);
				dc.FillSolidRect(pos.x,pos.y,34,34,m_NormalColor);
				Sleep(100);
				BiltBitmap(pos.x,pos.y,pos.x+33,pos.y+33,m_hWhite);
				Sleep(100);
				dc.FillSolidRect(pos.x,pos.y,34,34,m_NormalColor);
				Sleep(100);
				BiltBitmap(pos.x,pos.y,pos.x+33,pos.y+33,m_hWhite);
				DrawTable(point.x,point.y,T_WHITE);
				m_CurPlay=T_BLACK;
				if (!(pDoc->m_MainTable).HaveDown(T_BLACK))
				{
					if (!(pDoc->m_MainTable).HaveDown(T_WHITE))
					{
						pDoc->GameOver();
					}
					else
					{
						MessageBox("Black Pass!!!");
						m_CurPlay=T_WHITE;
						goto cont;
					}
				}
			}
			::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
			SetCursor(m_hcurDefault);
			DispDown(pDoc,&dc);
		}
		else
		{
			if (m_CurPlay==T_WHITE && (pDoc->m_MainTable).IsDown(m_CurCol,m_CurRow,T_WHITE))
			{
				BiltBitmap(m_CurX,m_CurY,m_CurX+33,m_CurY+33,m_hWhite);
				(pDoc->m_MainTable).SetTable(m_Current,T_WHITE);
				DrawTable(m_CurCol,m_CurRow,T_WHITE);
				if (!(pDoc->m_MainTable).HaveDown(T_BLACK))
				{
					if (!(pDoc->m_MainTable).HaveDown(T_WHITE))
					{
						MessageBox("Game Over!!!");
					}
					else
					{
						MessageBox("No!!!");
						m_CurPlay=T_WHITE;
					}
				}
				else
				{
					m_CurPlay=T_BLACK;
				}
				::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
				SetCursor(m_hcurDefault);
			}
		}
	}
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDown(nFlags, point);
}