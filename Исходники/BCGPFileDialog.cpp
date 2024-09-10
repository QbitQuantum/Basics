//***************************************************************************************
LRESULT CALLBACK CBCGPFileDialog::WindowProcNew(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_NOTIFY:
		{
			CBCGPFileDialog* pFD = GetBCGFileDlg (hwnd);

			LPNMHDR pHdr = (LPNMHDR) lParam;
			ASSERT (pHdr != NULL);

			if (wParam == iTabCtrlId && pHdr->code == TCN_SELCHANGE)
			{
				pFD->OnTabSelchange();
			}
			else if ((wParam == iNewListCtrlId || wParam == iRecentListCtrlId) 
				&& pHdr->code == NM_DBLCLK)
			{
				pFD->OnItemDblClick();
			}
		}
		break;

	case WM_COMMAND:
		{
			if ((int) LOWORD(wParam) == IDOK)
			{
				CBCGPFileDialog* pFD = GetBCGFileDlg (hwnd);
				if (pFD->GetPage () != CBCGPFileDialog::BCGFileOpen)
				{
					pFD->OnItemDblClick();
					return 0;
				}
			}
		}
		break;

	case WM_PAINT:
		{
			CBCGPFileDialog* pFD = GetBCGFileDlg (hwnd);
			pFD->CollectControls ();
	
			if (pFD->m_pBmpLogo != NULL)
			{
				ASSERT_VALID (pFD->m_pBmpLogo);

				CFileDialog* pDlg = (CFileDialog*)CWnd::FromHandle (hwnd);
				ASSERT (pDlg != NULL);

				CPaintDC dc (pDlg); // device context for painting
				dc.DrawState (pFD->m_rectLogo.TopLeft (),
					pFD->m_rectLogo.Size (), pFD->m_pBmpLogo,
					DSS_NORMAL);

				CRect rectFrame = pFD->m_rectLogo;
				rectFrame.InflateRect (1, 1);

				dc.Draw3dRect (rectFrame, globalData.clrBtnShadow, globalData.clrBtnLight);
			}
		}
		break;

	case WM_SIZE:
		{
			LRESULT lRes = CallWindowProc(CBCGPFileDialog::m_wndProc, hwnd, message, wParam, lParam);

			CBCGPFileDialog* pFD = GetBCGFileDlg (hwnd);
			ASSERT_VALID (pFD);

			CWnd* pFDParent = pFD->GetParent();
			ASSERT (pFDParent != NULL);

			CRect rectTabs;
			pFDParent->GetClientRect (rectTabs);
			rectTabs.DeflateRect (4, 4);
			rectTabs.top += pFD->m_iLogoAreaHeight;

			pFD->m_wndTab.SetWindowPos (NULL, -1, -1,
				rectTabs.Width (), rectTabs.Height (),
				SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

			pFD->m_lstFDControls.RemoveAll ();
			pFD->CollectControls ();

			return lRes;
		}
	}

	return CallWindowProc(CBCGPFileDialog::m_wndProc, hwnd, message, wParam, lParam);
}