int CTrackContrl::Track( const CPoint & point, UINT nFlags /* = 0 */,BOOL bTrackRubberBand /* = TRUE */ )
{
	ASSERT(m_pwndParent != NULL);
	CRect InitialBoundRect;
	int pX, pY;
	if(nFlags == MK_LBUTTON || nFlags== (MK_LBUTTON | MK_CONTROL)
		|| nFlags==(MK_LBUTTON | MK_SHIFT))
	{
		for(int i=0;i<m_selTrackerAll.GetSize();i++)
		{
			int Hit=m_selTrackerAll[i]->HitTest(point);//判断用户是否抓住了一个handle
			if(m_selTrackerAll[i]->GetCtrWindowIsable())
			{
				return TRACK_CTR_ABLE;
			}
			if(Hit!=CRectTracker::hitNothing)
			{
				//判断ctrl按下
				if( ( nFlags & MK_CONTROL ) != 0 )
				{
					Toggle( m_selTrackerAll[i] );
					return TRACK_CTR_CTRL;						
				}	
				//shift
				if( ( nFlags & MK_SHIFT ) != 0 )
				{
					Select( m_selTrackerAll[i] );
					return TRACK_CTR_SHIFT;
				}
				//没有ctrl shift时 这个控件被按下
				if(!IsSelected(m_selTrackerAll[i]))//在选中数组检测这个控件是否已经选中了
					DeSelectAll();//删除数组中所有选中
				Select( m_selTrackerAll[i] );//选中当前控件

				InitialBoundRect = GetBoundsRect();//获取没有移动前的CRect
				///////把没有移动前的Rect赋给当前TrackContrl的Rect
				m_rect.CopyRect( & InitialBoundRect );

				if(Hit ==  CRectTracker::hitMiddle)//用户抓住中间参见MSDN  CRectTracker::HitTest
				{
					CRectTracker::Track( m_pwndParent, point);//用户跟踪鼠标位置,并保存在m_rect中			
					pX = InitialBoundRect.left - m_rect.left;
					pY = InitialBoundRect.top - m_rect.top;
					
					// 把控件移动到鼠标位置
					for( int j = 0; j < m_selectRectTracker.GetSize(); j++ )
					{
						//鼠标左键选中的控件
						int Hit=m_selectRectTracker[j]->HitTest(point);
						if(!m_selectRectTracker[j]->GetCtrWindowIsable() && Hit != CRectTracker::hitNothing)
						{
							m_pRightBnSelect = m_selectRectTracker[j];	
						}
						/////////////////////////////////////////
						//////////////////////////////移动
						CRect rect;
						rect.left = m_selectRectTracker[j]->m_rect.left - pX;
						rect.right = m_selectRectTracker[j]->m_rect.right - pX;
						rect.top = m_selectRectTracker[j]->m_rect.top - pY;
						rect.bottom = m_selectRectTracker[j]->m_rect.bottom - pY;
						//和最大矩形对比
						ReAdjustMaxRect(rect,TRUE);
						m_selectRectTracker[j]->SetRect(rect);
						///////////////////////////////重画
						ReDrawRect(m_selectRectTracker[j]->m_rect,m_selectRectTracker[j]->m_nHandleSize);
					}
					/////重画Old区域
					ReDrawRect(InitialBoundRect,m_selTrackerAll[0]->m_nHandleSize);
				}
				else
				{
					/////////////////////////拉大，拉小
					m_selTrackerAll[i]->Track( m_pwndParent, point );
					/////////////////////////跟最大矩形做对比
					ReAdjustMaxRect(m_selTrackerAll[i]->m_rect);
					m_selTrackerAll[i]->SetRect(m_selTrackerAll[i]->m_rect);
					///////重画
					ReDrawRect(m_selTrackerAll[i]->m_rect,m_selTrackerAll[i]->m_nHandleSize);
					ReDrawRect(InitialBoundRect,m_selTrackerAll[i]->m_nHandleSize);
				}
				return TRACK_CTR_MIDORHANDLE;
			}
		}
		//用户鼠标没有抓住任何控件的handle	
		DeSelectAll();//删除保存的所有选中按钮
		//参数bTrackRubberBand用于是否画虚线框区域,参见TrackRubberBand函数,
		//即windows中用于选择区域的虚线框如在桌面上可以拖动一个虚线框选中n个图标
		if(!bTrackRubberBand)
		{
			m_pwndParent->Invalidate();
			return TRACK_CTR_RUBBERBAND;
		}
		TrackRubberBand( m_pwndParent, point );
		//  TrackRubberBand显示橡皮筋层（Windows中用于选择的虚线框），
		//	该函数一般在处理WM_LBUTTONDOWN消息的函数中被调用，
		//	函数中第一个参数是拥有橡皮筋长方形的窗体指针，第二个参数是点的坐标，
		//	第三个参数用于控制是否允许反向选择，即从右下角到左上角进行选择。
		m_rect.NormalizeRect();//一个正数的矩形，如果从下往上化矩形框，函数将交换top和bottom
		//同理，从右忘左画时交换left和right
		CRect temp;
		for(int k=0;k<m_selTrackerAll.GetSize();k++)
		{
			//intersectRect计算两个矩形的交集
			temp.IntersectRect(&m_rect,&m_selTrackerAll[k]->m_rect);
			//交集区域矩形等于控件矩形，选中
//			if(temp.EqualRect(&m_selTrackerAll[k]->m_rect))
//				Select(m_selTrackerAll[k]);
			if(!temp.IsRectEmpty())//如果交集区域不为空就选中
				Select(m_selTrackerAll[k]);
		}
		return TRACK_CTR_LBUTTON;
	}
	else if(nFlags & MK_RBUTTON)
	{
		int flag = TRACK_CTR_OTHER;
		for(int i=0;i<m_selTrackerAll.GetSize();i++)
		{
			int Hit=m_selTrackerAll[i]->HitTest(point);//判断用户是否抓住了一个handle
			if(m_selTrackerAll[i]->GetCtrWindowIsable())
			{
				flag = TRACK_CTR_ABLE;
				return flag;
			}
			if(Hit != CRectTracker::hitNothing)
			{
				if(!IsSelected(m_selTrackerAll[i]))//在选中数组检测这个控件是否已经选中了
					DeSelectAll();//删除数组中所有选中
				Select( m_selTrackerAll[i] );//选中当前控件
			
				m_pRightBnSelect = m_selTrackerAll[i];
				flag = TRACK_CTR_RBUTTON;
			}
		}
		return flag;
	}
	else 
	{
		return TRACK_CTR_OTHER;
	}
}