int mxExpressionTray::handleEvent (mxEvent *event)
{
	MDLCACHE_CRITICAL_SECTION_( g_pMDLCache );

	int iret = 0;

	if ( HandleToolEvent( event ) )
	{
		return iret;
	}

	switch ( event->event )
	{
	case mxEvent::Action:
		{
			iret = 1;
			switch ( event->action )
			{
			default:
				iret = 0;
				break;
			case IDC_EXPRESSIONCLASS:
				{
					int index = g_pExpressionClass->getSelectedIndex();
					if ( index >= 0 )
					{
						CExpClass *current = expressions->GetClass( index );
						if ( current )
						{
							// Switch classname
							expressions->ActivateExpressionClass( current );
							current->SelectExpression( 0 );
						}
					}
				}
				break;
			case IDC_CONTEXT_NEWEXP:
				g_pFlexPanel->NewExpression();
				break;
			case IDC_CONTEXT_EDITEXP:
				if ( m_nClickedCell != -1 )
				{
					g_pFlexPanel->EditExpression();
				}
				break;
			case IDC_CONTEXT_REVERT:
				if ( m_nClickedCell != -1 )
				{
					g_pFlexPanel->RevertExpression( m_nClickedCell );
				}
				break;
			case IDC_CONTEXT_SAVEEXP:
				if ( m_nClickedCell != -1 )
				{
					g_pFlexPanel->SaveExpression( m_nClickedCell );
				}
				break;
			case IDC_CONTEXT_DELETEXP:
				if ( m_nClickedCell != -1 )
				{
					g_pControlPanel->DeleteExpression( m_nClickedCell );
				}
				break;
			case IDC_TRAYSCROLL:
				{
					if (event->modifiers == SB_THUMBTRACK)
					{
						int offset = event->height;
						
						slScrollbar->setValue( offset );
						
						m_nTopOffset = offset;
						
						redraw();
					}
					else if ( event->modifiers == SB_PAGEUP )
					{
						int offset = slScrollbar->getValue();
						
						offset -= m_nGranularity;
						offset = max( offset, slScrollbar->getMinValue() );
						
						slScrollbar->setValue( offset );
						InvalidateRect( (HWND)slScrollbar->getHandle(), NULL, TRUE );
						
						m_nTopOffset = offset;
						
						redraw();
					}
					else if ( event->modifiers == SB_PAGEDOWN )
					{
						int offset = slScrollbar->getValue();
						
						offset += m_nGranularity;
						offset = min( offset, slScrollbar->getMaxValue() );
						
						slScrollbar->setValue( offset );
						InvalidateRect( (HWND)slScrollbar->getHandle(), NULL, TRUE );
						
						m_nTopOffset = offset;
						
						redraw();
					}
				}
				break;
			case IDC_AB:
				{
					AB();	
				}
				break;
			case IDC_THUMBNAIL_INCREASE:
				{
					ThumbnailIncrease();
				}
				break;
			case IDC_THUMBNAIL_DECREASE:
				{
					ThumbnailDecrease();
				}
				break;
			case IDC_CONTEXT_CREATEBITMAP:
				{
					if ( m_nClickedCell >= 0 )
					{
						CExpClass *active = expressions->GetActiveClass();
						if ( active )
						{
							CExpression *exp = active->GetExpression( m_nClickedCell );
							if ( exp )
							{
								active->SelectExpression( m_nClickedCell );
								exp->CreateNewBitmap( models->GetActiveModelIndex() );
								redraw();
							}
						}
					}
				}
				break;
			}
			break;
		}
	case mxEvent::MouseDown:
		{
			if ( !( event->buttons & mxEvent::MouseRightButton ) )
			{
				// Figure out cell #
				int cell = GetCellUnderPosition( event->x, event->y );
				CExpClass *active = expressions->GetActiveClass();
				if ( active )
				{

					if ( cell == m_nCurCell && cell >= 0 && cell < active->GetNumExpressions() )
					{
						mxETButton *btn = GetItemUnderCursor( event->x, event->y );
						if ( btn && btn->m_fnCallback )
						{	
							(this->*(btn->m_fnCallback))( cell );
							return iret;
						}
					}
					
					if ( cell >= 0 && cell < active->GetNumExpressions() )
					{
						active->SelectExpression( cell, event->modifiers & mxEvent::KeyShift ? false : true );

						int cx, cy, cw, ch;
						if ( ComputeRect( cell, cx, cy, cw, ch ) )
						{
							m_bDragging = true;
							m_nDragCell = cell;
							
							m_nXStart = (short)event->x;
							m_nYStart = (short)event->y;

							m_rcFocus.left = cx;
							m_rcFocus.top = cy;
							m_rcFocus.right = cx + cw;
							m_rcFocus.bottom = cy + ch - m_nDescriptionHeight;

							POINT pt;
							pt.x = pt.y = 0;
							ClientToScreen( (HWND)getHandle(), &pt );

							OffsetRect( &m_rcFocus, pt.x, pt.y );

							m_rcOrig = m_rcFocus;

							DrawFocusRect();
						}
					}
					else
					{
						Deselect();
						active->DeselectExpression();
						redraw();
					}
				}
			}
			iret = 1;
		}
		break;
	case mxEvent::MouseDrag:
		{
			if ( m_bDragging )
			{
				// Draw drag line of some kind
				DrawFocusRect();
	
				// update pos
				m_rcFocus = m_rcOrig;
				OffsetRect( &m_rcFocus, ( (short)event->x - m_nXStart ), 
					( (short)event->y - m_nYStart ) );
				
				DrawFocusRect();
			}
			iret = 1;
		}
		break;
	case mxEvent::MouseUp:
		{
			iret = 1;

			if ( event->buttons & mxEvent::MouseRightButton )
			{
				SetClickedCell( GetCellUnderPosition( (short)event->x, (short)event->y ) );
				ShowRightClickMenu( (short)event->x, (short)event->y );
				return iret;
			}

			int cell = GetCellUnderPosition( event->x, event->y );
			CExpClass *active = expressions->GetActiveClass();

			if ( m_bDragging )
			{
				DrawFocusRect();
				m_bDragging = false;
				// See if we let go on top of the choreo view

				if ( active )
				{
					// Convert x, y to screen space
					POINT pt;
					pt.x = (short)event->x;
					pt.y = (short)event->y;
					ClientToScreen( (HWND)getHandle(), &pt );

					HWND maybeTool = WindowFromPoint( pt );

					// Now tell choreo view
					CExpression *exp = active->GetExpression( m_nDragCell );
					if ( exp && maybeTool )
					{
						if ( IsWindowOrChild( g_pChoreoView, maybeTool ) )
						{
							if ( g_pChoreoView->CreateExpressionEvent( pt.x, pt.y, active, exp ) )
							{
								return iret;
							}
						}
					
						if ( IsWindowOrChild( g_pExpressionTool, maybeTool ) )
						{
							if ( g_pExpressionTool->SetFlexAnimationTrackFromExpression( pt.x, pt.y, active, exp ) )
							{
								return iret;
							}
						}
					}
				}
			}

			if ( active )
			{
				// Over a new cell
				if ( cell >= 0 && 
					cell < active->GetNumExpressions() && 
					cell != m_nCurCell &&
					m_nCurCell != -1 )
				{
					// Swap cells
					CExpression *exp = active->GetExpression( m_nCurCell );
					if ( exp )
					{
						active->SwapExpressionOrder( m_nCurCell, cell );
						active->SetDirty( true );
						active->SelectExpression( cell );
					}
				}
			}
		}
		break;
	case mxEvent::Size:
		{
			int width = w2();

			int ch = GetCaptionHeight();

			g_pExpressionClass->setBounds( 5, 5 + ch, width - 120, 20 );

			m_pABButton->setBounds( width - 60, 4 + ch, 60, 16 );
			m_pThumbnailIncreaseButton->setBounds( width - 60 - 40, 4 + ch, 16, 16 );
			m_pThumbnailDecreaseButton->setBounds( width - 60 - 20, 4 + ch, 16, 16 );

			m_nTopOffset = 0;
			RepositionSlider();

			redraw();
			iret = 1;
		}
		break;
	case mxEvent::MouseWheeled:
		{
			// Figure out cell #
			POINT pt;

			pt.x = event->x;
			pt.y = event->y;

			ScreenToClient( (HWND)getHandle(), &pt );

			if ( event->height < 0 )
			{
				m_nTopOffset = min( m_nTopOffset + 10, slScrollbar->getMaxValue() );
			}
			else
			{
				m_nTopOffset = max( m_nTopOffset - 10, 0 );
			}
			RepositionSlider();
			redraw();
			iret = 1;
		}
		break;
	};

	if ( iret )
	{
		SetActiveTool( this );
	}
	return iret;
}