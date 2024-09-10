// ¶Ô»°¿ò»Øµ÷º¯Êý
inline LRESULT CALLBACK CalendarProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
				EndDialog(hDlg, TRUE);
				return TRUE;
			}
			break;
		case IDM_EATZAC:
			if (fMealMap[m_iDay-1]==M100 || fMealMap[m_iDay-1]==M101 || fMealMap[m_iDay-1]==M110 || fMealMap[m_iDay-1]==M111)
			{
				// <-Ôç²Í>
				fMealMap[m_iDay-1] -= M100;
				fTotalFee += M100;
			}
			else {
				// <+Ôç²Í>
				fMealMap[m_iDay-1] += M100;
				fTotalFee -= M100;
			}
			ShowMealData(hDlg);
			SaveMealMap();
			return TRUE;
			break;
		case IDM_EATWUC:
			if (fMealMap[m_iDay-1]==M010 || fMealMap[m_iDay-1]==M011 || fMealMap[m_iDay-1]==M110 || fMealMap[m_iDay-1]==M111)
			{
				// <-Îç²Í>
				fMealMap[m_iDay-1] -= M010;
				fTotalFee += M010;
			}
			else {
				// <+Îç²Í>
				fMealMap[m_iDay-1] += M010;
				fTotalFee -= M010;
			}
			ShowMealData(hDlg);
			SaveMealMap();
			return TRUE;
			break;
		case IDM_EATWAC:
			if (fMealMap[m_iDay-1]==M001 || fMealMap[m_iDay-1]==M101 || fMealMap[m_iDay-1]==M011 || fMealMap[m_iDay-1]==M111)
			{
				// <-Íí²Í>
				fMealMap[m_iDay-1] -= M001;
				fTotalFee += (M001-(float)0.1);
			}
			else {
				// <+Íí²Í>
				fMealMap[m_iDay-1] += M001;
				fTotalFee -= (M001-(float)0.1);

				//wchar_t szTmp[50] = { 0 };
				//char strTmp[50] = { 0 };
				//sprintf_s(strTmp, "fMealMap[m_iDay-1]: %.1f, fTotalFee: %.1f", fMealMap[m_iDay - 1], fTotalFee);
				//MultiByteToWideChar(CP_OEMCP, NULL, strTmp, 50, szTmp, 50);
				//MessageBox(NULL, szTmp, _T("OK"), MB_OK);
			}
			ShowMealData(hDlg);
			SaveMealMap();
			return TRUE;
			break;
		}
		return FALSE;
		break;
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			GetCursorPos(&pt);
			m_iDay = (WORD)SelectDay(hDlg, &pt);
			if (m_iDay == 0) {
				return TRUE;
			}
			PaintCalc(hDlg);
			if (uMsg == WM_RBUTTONDOWN) {
				CString menu1, menu2, menu3, menu4;
				if (fMealMap[m_iDay-1] == M000)
				{
					menu1.Format(_T("+Ôç²Í"));
					menu2.Format(_T("+Îç²Í"));
					menu3.Format(_T("+Íí²Í"));
					menu4.Format(_T("*Î´³Ô"));
				}
				else if (fMealMap[m_iDay-1] == M110)
				{
					menu1.Format(_T("-Ôç²Í"));
					menu2.Format(_T("-Îç²Í"));
					menu3.Format(_T("+Íí²Í"));
					menu4.Format(_T("*ÔçÎç"));
				}
				else if (fMealMap[m_iDay-1] == M111)
				{
					menu1.Format(_T("-Ôç²Í"));
					menu2.Format(_T("-Îç²Í"));
					menu3.Format(_T("-Íí²Í"));
					menu4.Format(_T("*È«³Ô"));
				}
				else if (fMealMap[m_iDay-1] == M100)
				{
					menu1.Format(_T("-Ôç²Í"));
					menu2.Format(_T("+Îç²Í"));
					menu3.Format(_T("+Íí²Í"));
					menu4.Format(_T("*Ôç²Í"));
				}
				else if (fMealMap[m_iDay-1] == M010)
				{
					menu1.Format(_T("+Ôç²Í"));
					menu2.Format(_T("-Îç²Í"));
					menu3.Format(_T("+Íí²Í"));
					menu4.Format(_T("*Îç²Í"));
				}
				else if (fMealMap[m_iDay-1] == M001)
				{
					menu1.Format(_T("+Ôç²Í"));
					menu2.Format(_T("+Îç²Í"));
					menu3.Format(_T("-Íí²Í"));
					menu4.Format(_T("*Íí²Í"));
				}
				else if (fMealMap[m_iDay-1] == M101)
				{
					menu1.Format(_T("-Ôç²Í"));
					menu2.Format(_T("+Îç²Í"));
					menu3.Format(_T("-Íí²Í"));
					menu4.Format(_T("*ÔçÍí"));
				}
				else if (fMealMap[m_iDay-1] == M011)
				{
					menu1.Format(_T("+Ôç²Í"));
					menu2.Format(_T("-Îç²Í"));
					menu3.Format(_T("-Íí²Í"));
					menu4.Format(_T("*ÎçÍí"));
				}

				ClientToScreen(hDlg, &pt);
				HMENU hMenu = CreatePopupMenu();
				AppendMenu(hMenu, MF_STRING, IDM_EATZAC, menu1);
				AppendMenu(hMenu, MF_STRING, IDM_EATWUC, menu2);
				AppendMenu(hMenu, MF_STRING, IDM_EATWAC, menu3);
				AppendMenu(hMenu, MF_STRING|MF_DISABLED|MF_GRAYED, IDM_EATNOW, menu4);
				TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, NULL, hDlg, NULL);
			}
			return TRUE;
		}
		break;
	case WM_WINDOWPOSCHANGED:
		PostMessage(hDlg, WM_SHOWCAL, 0, 0);
		return TRUE;
		break;
	case WM_SHOWCAL:
		PaintCalc(hDlg);
		ShowMealData(hDlg);
		return TRUE;
		break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return FALSE;
}