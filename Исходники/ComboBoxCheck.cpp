extern "C" static LRESULT FAR PASCAL ComboBoxCheckProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch (nMsg)
	{
	case WM_CHAR:
		{
			if (wParam == VK_SPACE)
			{
				INT nIndex = CallWindowProcA(_pWndProc, hWnd, LB_GETCURSEL, wParam, lParam);
				
				CRect rec;
				SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(LPVOID) &rec);
				::InvalidateRect(hWnd, rec, FALSE);
				_pComboBoxCheck->SetCheck(nIndex, !_pComboBoxCheck->GetCheck(nIndex));
				_pComboBoxCheck->GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetWindowLong(_pComboBoxCheck->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM)_pComboBoxCheck->m_hWnd);
				return 0;
			}
			break;
		}
		
	case WM_RBUTTONDOWN:
		{
			if (_pComboBoxCheck != NULL)
			{
				INT nCount = _pComboBoxCheck->GetCount();

				INT nSelectCount = 0;
				for (INT i = 0; i < nCount; i++)
					if (_pComboBoxCheck->GetCheck(i))
						nSelectCount++;
					
				::InvalidateRect(hWnd, 0, FALSE);
				_pComboBoxCheck->SelectAll(FALSE/*nSelectCount != nCount*/);
				_pComboBoxCheck->GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetWindowLong(_pComboBoxCheck->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM) _pComboBoxCheck->m_hWnd);
			}
		}
		break;
		
	case WM_LBUTTONUP:
		return 0;
		
	case WM_LBUTTONDOWN:
		{
			CRect recClient;
			GetClientRect(hWnd, recClient);
			
			CPoint pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			
			if (PtInRect(recClient, pt))
			{
				INT nHeight = SendMessage(hWnd, LB_GETITEMHEIGHT, 0, 0);
				INT nTopIndex = SendMessage(hWnd, LB_GETTOPINDEX, 0, 0);
				
				INT nIndex = nTopIndex + pt.y / nHeight;
				
				CRect rec;
				SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(LPVOID) &rec);
				if (PtInRect(rec, pt))
				{
					::InvalidateRect(hWnd, rec, FALSE);
					_pComboBoxCheck->SetCheck(nIndex, !_pComboBoxCheck->GetCheck(nIndex));
					_pComboBoxCheck->GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetWindowLong(_pComboBoxCheck->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM)_pComboBoxCheck->m_hWnd);
				}
			}
		}
		break;
		
	case LB_GETCURSEL:
		return -1;
	}
	
	return CallWindowProc(_pWndProc, hWnd, nMsg, wParam, lParam);
}