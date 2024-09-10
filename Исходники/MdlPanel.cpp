void CMdlPanel::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 没按下按键时候的检测，用于在不同位置显示不同光标
	if ( (nFlags & MK_LBUTTON) == 0 && (nFlags & MK_LBUTTON) == 0)
	{
		m_action = NONE_ACTION;
		//------------ 如果落在在某个组件的某个输出端口内，则可以进行连线操作 ----------------------------
		for (unsigned int i = 0; i < g_pApp->m_miseModel.components.size(); i++)
		{
			for ( unsigned int j = 0; j < g_pApp->m_miseModel.components[i]->outputs.size(); j++)
			{
				CRect rectTmp(	g_pApp->m_miseModel.components[i]->outputs[j].pos.x,
								g_pApp->m_miseModel.components[i]->outputs[j].pos.y - IO_ARROW_SIZE,
								g_pApp->m_miseModel.components[i]->outputs[j].pos.x + IO_ARROW_SIZE,
								g_pApp->m_miseModel.components[i]->outputs[j].pos.y + IO_ARROW_SIZE
							 );
				if(rectTmp.PtInRect(point))
				{
					m_action = CONN_COMP;	//标识当前为连线操作
					return;
				}
			}
		}
		// ------------- 如果落在某个模块的边线范围内，则可以进行改变大小的操作 -----------------------------
		for (unsigned int i = g_pApp->m_miseModel.components.size(); i > 0 ; i-- )
		{
			if ( g_pApp->m_miseModel.components[i - 1]->rect.PtInRect(point) )
			{
				if ( point.x - g_pApp->m_miseModel.components[i - 1]->rect.left < SEL_SENSITIVITY )
				{
					m_action = RESZ_COMP_LEFT;
				}
				else if ( g_pApp->m_miseModel.components[i - 1]->rect.right - point.x < SEL_SENSITIVITY )
				{
					m_action = RESZ_COMP_RIGHT;
				}
				
				else if ( point.y - g_pApp->m_miseModel.components[i - 1]->rect.top < SEL_SENSITIVITY )
				{
					m_action = RESZ_COMP_TOP;
				}
				else if ( g_pApp->m_miseModel.components[i - 1]->rect.bottom - point.y < SEL_SENSITIVITY )
				{
					m_action = RESZ_COMP_BOTTOM;
				}
				break;
			}
		}

		return CView::OnMouseMove(nFlags, point);
	}



	//---------------- 拖动组件操作 ----------------------------------------------------
	if (m_action == SLCT_COMP)		//当前为选择组件的操作
	{
		//按住左键时的拖动
		if ( nFlags == MK_LBUTTON )
		{
			BOOL needRefresh = FALSE;
			MiseComponent *pComponent = 0;
			for ( unsigned int i = 0; i < g_pApp->m_miseModel.components.size(); i++ )
			{
				if (g_pApp->m_miseModel.components[i]->isSelected)
				{
					pComponent = g_pApp->m_miseModel.components[i];
					pComponent->Move(point.x - m_oldPoint.x, point.y - m_oldPoint.y);
					needRefresh = TRUE;
				}
			}
			if (needRefresh)
			{
				this->Invalidate();
			}
		}
	}
	//----------------- end of 拖动组件操作 --------------------------------------------

	//----------------- 连线操作 -------------------------------------------------------
	else if ( nFlags == MK_LBUTTON && m_action == CONN_COMP)
	{
		int break1x;		//第一个拐点的x坐标
		int break2y;		//第二个拐点的y坐标
		int break3x;		//第三个拐点的x坐标，如果为-1，则无第三个和第四个拐点
		BOOL need4breaks = FALSE;	//标识是否需要四个拐点

		CDC* pDC;
		pDC = this->GetDC();
		pDC->SetROP2(R2_NOTXORPEN);	//设定画线模式，便于擦除原来的连线

		//首先擦除原连线
		if ( m_oldPoint.x - m_startPoint.x > BREAK_SPACE )
		{
			break1x = (m_startPoint.x + m_oldPoint.x) / 2;
			need4breaks = FALSE;
		}
		else
		{
			break1x = m_startPoint.x + BREAK_SPACE / 2;
			break2y = (m_startPoint.y + m_oldPoint.y) / 2;
			break3x = m_oldPoint.x - BREAK_SPACE / 2;
			need4breaks = TRUE;
		}


		pDC->MoveTo(m_startPoint);
		if ( !need4breaks )
		{
			pDC->LineTo(break1x, m_startPoint.y);
			pDC->LineTo(break1x, m_oldPoint.y);
			pDC->LineTo(m_oldPoint);
		}
		else
		{
			pDC->LineTo(break1x, m_startPoint.y);
			pDC->LineTo(break1x, break2y);
			pDC->LineTo(break3x, break2y);
			pDC->LineTo(break3x, m_oldPoint.y);
			pDC->LineTo(m_oldPoint);
		}

		//重新画线
		if ( point.x - m_startPoint.x > BREAK_SPACE )
		{
			break1x = (m_startPoint.x + point.x) / 2;
			need4breaks = FALSE;
		}
		else
		{
			break1x = m_startPoint.x + BREAK_SPACE / 2;
			break2y = (m_startPoint.y + point.y) / 2;
			break3x = point.x - BREAK_SPACE / 2;
			need4breaks = TRUE;
		}

		pDC->MoveTo(m_startPoint);
		if ( !need4breaks )
		{
			pDC->LineTo(break1x, m_startPoint.y);
			pDC->LineTo(break1x, point.y);
			pDC->LineTo(point);
		}
		else
		{
			pDC->LineTo(break1x, m_startPoint.y);
			pDC->LineTo(break1x, break2y);
			pDC->LineTo(break3x, break2y);
			pDC->LineTo(break3x, point.y);
			pDC->LineTo(point);
		}

		ReleaseDC(pDC);
	}
	//------------ end of 连线 --------------------------------------------------------------------
	
	//------------ 拖动连线的操作 -----------------------------------------------------------------
	else if ( nFlags == MK_LBUTTON && m_action == SLCT_LINE)
	{
		CDC* pDC;
		pDC = this->GetDC();
		pDC->SetROP2(R2_NOTXORPEN);	//设定画线模式，便于擦除原来的连线
		unsigned int i;
		//只处理第一条被选中的连线，首先找到这条连线
		for( i = 0; i < g_pApp->m_miseModel.connlines.size(); i++)
		{
			if(g_pApp->m_miseModel.connlines[i].m_isSelected)
			{
				break;
			}
		}

		if(i < g_pApp->m_miseModel.connlines.size())
		{
			CPen newPen, *oldPen;
			newPen.CreatePen(PS_SOLID, 1, SLCT_LINE_CLR);
			oldPen = pDC->SelectObject(&newPen);
			//如果只有两个拐点
			if(g_pApp->m_miseModel.connlines[i].break2y == -1 )
			{
				//只处理对第二段的拖动
				if(g_pApp->m_miseModel.connlines[i].selectedPart == 2)
				{
					//擦除原连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);

					//修正break1x
					g_pApp->m_miseModel.connlines[i].break1x = point.x;

					//重新连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);
				}
			}
			//如果有四个拐点
			else
			{
				//处理第二段的拖动
				if(g_pApp->m_miseModel.connlines[i].selectedPart == 2)
				{
					//擦除原连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x,g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);

					//修正break1x
					g_pApp->m_miseModel.connlines[i].break1x = point.x;

					//重新连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x,g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);
				}

				//处理第三段的拖动
				else if(g_pApp->m_miseModel.connlines[i].selectedPart == 3)
				{
					//擦除原连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x,g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);

					//修正break1x
					g_pApp->m_miseModel.connlines[i].break2y = point.y;

					//重新连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x,g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);
				}

				//处理第四段的拖动
				else if(g_pApp->m_miseModel.connlines[i].selectedPart == 4)
				{
					//擦除原连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x,g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);

					//修正break1x
					g_pApp->m_miseModel.connlines[i].break3x = point.x;

					//重新连线
					pDC->MoveTo(g_pApp->m_miseModel.connlines[i].startPoint);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x,g_pApp->m_miseModel.connlines[i].startPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break1x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].break2y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].break3x, g_pApp->m_miseModel.connlines[i].endPoint.y);
					pDC->LineTo(g_pApp->m_miseModel.connlines[i].endPoint);
				}
			}
			pDC->SelectObject(oldPen);
			newPen.DeleteObject();

		}
	}

	//------------ end of 拖动连线 ----------------------------------------------------------------

	//------------ 改变模块大小 -------------------------------------------------------------------
	else if(m_action == RESZ_COMP_RIGHT )
	{
		for ( unsigned int i = 0; i < g_pApp->m_miseModel.components.size(); i++ )
		{
			if (g_pApp->m_miseModel.components[i]->isSelected)
			{
				if ( point.x - g_pApp->m_miseModel.components[i]->rect.left > COM_MINSIZE )
				{
					CRect rect = g_pApp->m_miseModel.components[i]->rect;
					rect.right = point.x;

					g_pApp->m_miseModel.components[i]->MoveEx(rect);
					this->Invalidate();
				}
			}
		}
	}
	else if(m_action == RESZ_COMP_LEFT )
	{
		for ( unsigned int i = 0; i < g_pApp->m_miseModel.components.size(); i++ )
		{
			if (g_pApp->m_miseModel.components[i]->isSelected)
			{
				if ( g_pApp->m_miseModel.components[i]->rect.right - point.x > COM_MINSIZE )
				{
					CRect rect = g_pApp->m_miseModel.components[i]->rect;
					rect.left = point.x;

					g_pApp->m_miseModel.components[i]->MoveEx(rect);
					this->Invalidate();
				}
			}
		}
	}
	else if(m_action == RESZ_COMP_TOP )
	{
		for ( unsigned int i = 0; i < g_pApp->m_miseModel.components.size(); i++ )
		{
			if (g_pApp->m_miseModel.components[i]->isSelected)
			{
				if ( g_pApp->m_miseModel.components[i]->rect.bottom - point.y > COM_MINSIZE )
				{
					CRect rect = g_pApp->m_miseModel.components[i]->rect;
					rect.top = point.y;

					g_pApp->m_miseModel.components[i]->MoveEx(rect);
					this->Invalidate();
				}
			}
		}
	}
	else if(m_action == RESZ_COMP_BOTTOM )
	{
		for ( unsigned int i = 0; i < g_pApp->m_miseModel.components.size(); i++ )
		{
			if (g_pApp->m_miseModel.components[i]->isSelected)
			{
				if ( point.y - g_pApp->m_miseModel.components[i]->rect.top > COM_MINSIZE )
				{
					CRect rect = g_pApp->m_miseModel.components[i]->rect;
					rect.bottom = point.y;

					g_pApp->m_miseModel.components[i]->MoveEx(rect);
					this->Invalidate();
				}
			}
		}
	}

	m_oldPoint = point;

	CView::OnMouseMove(nFlags, point);
}