LRESULT CALLBACK CListSide::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		{
			int nScrollNotify = -1;

			bool bFoundT = false, bFoundS = false;
			HWND hEdit = GetFocus();
			CListSide* pThis = (CListSide*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
			deque<CListSide::LINE>::iterator I;
			for (I = pThis->m_Lines.begin(); I != pThis->m_Lines.end(); I++)
			{
				if (I->edText.m_hWnd == hEdit)
				{
					bFoundT = true;
					break;
				}
				if (I->edSecond.m_hWnd == hEdit)
				{
					bFoundS = true;
					break;
				}
			}

			switch (wParam)
			{
			case VK_SHIFT: break;
			case VK_NEXT:
				nScrollNotify = SB_PAGEDOWN; break;
			case VK_PRIOR:
				nScrollNotify = SB_PAGEUP; break;
			case VK_HOME:
				nScrollNotify = SB_TOP; break;
			case VK_END:
				nScrollNotify = SB_BOTTOM; break;
			case VK_UP:
				{	
					if (I->nIndex != 0)
					{
						if (bFoundT)
							SetFocus(pThis->m_Lines.at(I->nIndex - 1).edText.m_hWnd);
						if (bFoundS)
							SetFocus(pThis->m_Lines.at(I->nIndex - 1).edSecond.m_hWnd);
						
						RECT rect;
						GetWindowRect(pThis->m_Lines[I->nIndex-1].edText.m_hWnd, &rect);
						POINT pt = {rect.left, rect.top};
						ScreenToClient(hWnd, &pt);
						if (0 > pt.y || pThis->m_dPage < pt.y)
							pThis->ScrollTo(pt.y + pThis->m_dScrollPos);
						else
						{
							GetWindowRect(pThis->m_Lines[I->nIndex].edText.m_hWnd, &rect);
							pt.x = rect.left; pt.y = rect.top;
							ScreenToClient(hWnd, &pt);
							if (pt.y < 0)
								nScrollNotify = SB_LINEUP;
						}
					}
					
				}
				break;
			case VK_DOWN:
				{	
					if (I->nIndex != pThis->m_Lines.back().nIndex)
					{
						if (bFoundT)
							SetFocus(pThis->m_Lines.at(I->nIndex + 1).edText.m_hWnd);
						if (bFoundS)
							SetFocus(pThis->m_Lines.at(I->nIndex + 1).edSecond.m_hWnd);

				
						RECT rect;
						GetWindowRect(pThis->m_Lines[I->nIndex + 1].edText.m_hWnd, &rect);
						POINT pt = {rect.right, rect.bottom};
						ScreenToClient(hWnd, &pt);

						if (pThis->m_dScrollPos > pt.y || pThis->m_dScrollPos + pThis->m_dPage - 1 < pt.y)
							pThis->ScrollTo(pt.y + pThis->m_dScrollPos - pThis->m_dPage);
						else
						{
							GetWindowRect(pThis->m_Lines[I->nIndex].edText.m_hWnd, &rect);
							pt.x = rect.left; pt.y = rect.bottom;
							ScreenToClient(hWnd, &pt);
							if (pt.y  >= pThis->m_dPage)
								nScrollNotify = SB_LINEDOWN;
						}
						
					} 
				}
				break;

			default:
				{	
					if (!bFoundT && !bFoundS) break;
					RECT rect;
					GetWindowRect(pThis->m_Lines[I->nIndex].edText.m_hWnd, &rect);
					POINT pt = {rect.left, rect.top};
					ScreenToClient(hWnd, &pt);
					if (0 > pt.y || pThis->m_dPage < pt.y)
						pThis->ScrollTo(pt.y + pThis->m_dScrollPos);
					else
					{
						GetWindowRect(pThis->m_Lines[I->nIndex].edText.m_hWnd, &rect);
						pt.x = rect.left; pt.y = rect.top;
						ScreenToClient(hWnd, &pt);
						if (pt.y < 0)
							nScrollNotify = SB_LINEUP;
					}
				}
				break;
			}

			if (nScrollNotify!=-1)
			{
				SendMessage(hWnd, WM_VSCROLL, MAKEWPARAM(nScrollNotify,0), 0);
			}
		}
		break;//WM_KEYDOWN

	case WM_MOUSEWHEEL:
		{
			INT16 delta = (int)HIWORD(wParam);
			if (delta < 0)
				SendMessage(hWnd, WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN,0), 0);
			else
				SendMessage(hWnd, WM_VSCROLL, MAKEWPARAM(SB_LINEUP,0), 0);
		}
		break;

//	case WM_PAINT: break;
	case WM_VSCROLL: OnVScroll(hWnd, wParam, lParam); break;
	case WM_ADDLINEAT:
		{
			CListSide* pThis = (CListSide*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
			int nLine = LOWORD(wParam);
			int nSelEnd = HIWORD(wParam);
			HWND hEdit = (HWND)lParam;

			pThis->AddLineAt(nLine+1);
			int end = GetWindowTextLengthW(hEdit);
			SendMessage(hEdit, EM_SETSEL, (WPARAM)nSelEnd, (LPARAM)end);
			
			if (nSelEnd < end)
			{
				SendMessage(hEdit, WM_CUT, 0, 0);
				hEdit = pThis->m_Lines.at(nLine + 1).edText.m_hWnd;
				SendMessage(hEdit, WM_PASTE, 0, 0);
			}
			else
				hEdit = pThis->m_Lines.at(nLine + 1).edText.m_hWnd;

			SetFocus(hEdit);
			SendMessage(hEdit, EM_SETSEL, 0, 0);
		}
		break;

	case WM_DELLINEAT:
		{
			CListSide* pThis = (CListSide*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
			int nLine = (int)wParam;
			HWND hEdit= (HWND)lParam;

			//1. copy the content from this line:
			int len = GetWindowTextLengthA(hEdit);
			len++;
			char* str = new char[len];
			int len2;
			if (0 < len)
			{
				GetWindowTextA(hEdit, str, len);
				hEdit = pThis->m_Lines.at(nLine - 1).edText.m_hWnd;
				len2 = GetWindowTextLengthA(hEdit);
				len2++;
				char* str2 = new char[len2];
				GetWindowTextA(hEdit, str2, len2);
				string sir = str2;
				sir += ' ';
				sir += str;
				SetWindowTextA(hEdit, sir.data());
				delete[] str2;
			}
			else
				hEdit = pThis->m_Lines.at(nLine - 1).edText.m_hWnd;

			//2. move cursor to the editbox above
			pThis->RemoveLineAt(nLine+1);
			SetFocus(hEdit);
			SendMessage(hEdit, EM_SETSEL, len2, len2);
			delete[] str;
		}
		break;

	case WM_DELLINEDELAT:
		{
			//using DEL
			CListSide* pThis = (CListSide*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
			int nLine = (int)wParam;
			HWND hEdit= (HWND)lParam;

			//1. copy the content from this line:
			int len = GetWindowTextLengthA(hEdit);
			len++;
			char* str = new char[len];
			int len2;
			string sir;
			if (0 < len)
			{
				GetWindowTextA(hEdit, str, len);
				hEdit = pThis->m_Lines.at(nLine - 1).edText.m_hWnd;
				len2 = GetWindowTextLengthA(hEdit);
				len2++;
				char* str2 = new char[len2];
				GetWindowTextA(hEdit, str2, len2);
				sir = str2;
				sir += ' ';
				sir += str;
				delete[] str2;
			}
			else
				hEdit = pThis->m_Lines.at(nLine - 1).edText.m_hWnd;

			//2. move cursor to the editbox above
			pThis->RemoveLineAt(nLine);
			SetWindowTextA(hEdit, sir.data());
			SetFocus(hEdit);
			SendMessage(hEdit, EM_SETSEL, len2, len2);
			delete[] str;
		}
		break;
		
	case WM_SELECTLINE:
		{
			CListSide* pThis = (CListSide*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
			if (pThis->m_bEnableLineSel == false)
				break;

			int nLine = (int)wParam;
			if (pThis->m_nSelLine > -1)
			{
				pThis->m_Lines.at(pThis->m_nSelLine).bSelected = false;
				RedrawWindow(pThis->m_Lines.at(pThis->m_nSelLine).edText.m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
				RedrawWindow(pThis->m_Lines.at(pThis->m_nSelLine).edSecond.m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
			}
			if (pThis->m_nSelLine != nLine)
			{
				pThis->m_nSelLine = nLine;
				pThis->m_Lines.at(nLine).bSelected = true;
				RedrawWindow(pThis->m_Lines.at(nLine).edText.m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
				RedrawWindow(pThis->m_Lines.at(nLine).edSecond.m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);

				RECT rect;
				GetWindowRect(pThis->m_Lines[nLine].edText.m_hWnd, &rect);
				POINT pt = {rect.right, rect.bottom};
				ScreenToClient(hWnd, &pt);

				if (pThis->m_dScrollPos > pt.y || pThis->m_dScrollPos + pThis->m_dPage - 1 < pt.y || pt.y  >= pThis->m_dPage)
					pThis->ScrollTo(pt.y + pThis->m_dScrollPos - pThis->m_dPage);
			}
			else pThis->m_nSelLine = -1;
		}
		break;//WM_SELECTLINE

	case WM_CTLCOLOREDIT:
		{
			HDC hDC = (HDC)wParam;
			HWND hEdit = (HWND)lParam;
			HBRUSH hBrush = 0;
			
			CListSide* pThis = (CListSide*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
			bool bFound = false;
			deque<CListSide::LINE>::iterator I;
			for (I = pThis->m_Lines.begin(); I != pThis->m_Lines.end(); I++)
			{
				if (hEdit == I->edSecond.m_hWnd || hEdit == I->edText.m_hWnd)
				{
					//we found the edit in the list
					if (I->bSelected)
					{
						//the edit is selected
						hBrush = CreateSolidBrush(RGB(0, 0, 255));
						SetBkColor(hDC, RGB(0, 0, 255));
						SetTextColor(hDC, RGB(255, 255, 255));
						break;
					}
					else
					{
						//the edit is not selected
						hBrush = CreateSolidBrush(RGB(255, 255, 255));
						SetBkColor(hDC, RGB(255, 255, 255));
						SetTextColor(hDC, RGB(0, 0, 0));
					}
				}
				//if we did not find the edit in the list, we keep searching, to know whether it is selected or not
			}
			return (LRESULT)hBrush;
		}
		break;//WM_CTLCOLOREDIT
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}