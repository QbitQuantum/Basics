/*
 * Function CHyperLink::_HyperlinkProc
 *
 * Note: Processed messages are not passed back to the static control
 *       procedure. It does work fine but be aware that it could cause
 *       some problems if the static control is already subclassed.
 *       Consider the example where the static control would be already
 *       subclassed with the ToolTip control that needs to process mouse
 *       messages. In that situation, the ToolTip control would not work
 *       as expected.
 */
LRESULT CALLBACK CHyperLink::_HyperlinkProc(HWND hwnd, UINT message,
		                                   WPARAM wParam, LPARAM lParam)
{
	CHyperLink *pHyperLink = (CHyperLink *)GetProp(hwnd, PROP_OBJECT_PTR);

	switch (message)
	{
	case WM_MOUSEMOVE:
		{
			if ( pHyperLink->m_bOverControl )
			{
				// This is the most common case for static branch prediction
				// optimization
				RECT rect;
				GetClientRect(hwnd,&rect);

				POINT pt = { LOWORD(lParam), HIWORD(lParam) };

				if (!PTINRECT(&rect,pt))
				{
					ReleaseCapture();
				}
			}
			else
			{
				pHyperLink->m_bOverControl = TRUE;
				SendMessage(hwnd, WM_SETFONT,
					        (WPARAM)CHyperLink::g_UnderlineFont, FALSE);
				InvalidateRect(hwnd, NULL, FALSE);
				pHyperLink->OnSelect();
				SetCapture(hwnd);
			}
			return 0;
		}
	case WM_SETCURSOR:
		{
			SetCursor(CHyperLink::g_hLinkCursor);
			return TRUE;
		}
	case WM_CAPTURECHANGED:
		{
			pHyperLink->m_bOverControl = FALSE;
			pHyperLink->OnDeselect();
			SendMessage(hwnd, WM_SETFONT,
				        (WPARAM)pHyperLink->m_StdFont, FALSE);
			InvalidateRect(hwnd, NULL, FALSE);
			return 0;
		}
	case WM_KEYUP:
		{
			if( wParam != VK_SPACE )
			{
				break;
			}
		}
						// Fall through
	case WM_LBUTTONUP:
		{
			pHyperLink->Navigate();
			return 0;
		}
	case WM_SETFOCUS:	// Fall through
	case WM_KILLFOCUS:
		{
			if( message == WM_SETFOCUS )
			{
				pHyperLink->OnSelect();
			}
			else		// WM_KILLFOCUS
			{
				pHyperLink->OnDeselect();
			}
			CHyperLink::DrawFocusRect(hwnd);
			return 0;
		}
	case WM_DESTROY:
		{
			SetWindowLongPtr(hwnd, GWLP_WNDPROC,
				          (LONG) pHyperLink->m_pfnOrigCtlProc);

			SendMessage(hwnd, WM_SETFONT, (WPARAM) pHyperLink->m_StdFont, 0);

			if( --CHyperLink::g_counter <= 0 )
			{
				destroyGlobalResources();
			}

			RemoveProp(hwnd, PROP_OBJECT_PTR);
			break;
		}
	}

	return CallWindowProc(pHyperLink->m_pfnOrigCtlProc, hwnd, message,
		                  wParam, lParam);
}