INT_PTR CALLBACK TwoGameOverPro(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static HWND hCtrlBlock;
	static int num = 0;
	HDC hDC = 0;
	PAINTSTRUCT PtStr;
	switch (message)
	{
	case WM_TIMER:
		SetTimer(hDlg, 0, 10000, 0);
		if (num) {
			KillTimer(hDlg, 0);
			PostMessage(hDlg, WM_CLOSE, wParam, lParam);
		}
		num++;
		break;
	case WM_INITDIALOG:
	{
		return (INT_PTR)TRUE;
	}
	case WM_PAINT:
	{
		char str1[20] = "YOU FOOD:";
		char str2[20] = "YOU SCORE:";
		char str3[20] = { 0 };
		hDC = BeginPaint(hDlg, &PtStr);
		_itoa_s(Point_A, str3, 20);
		strcat_s(str1, str3);
		strcat_s(str2, str3);
		strcat_s(str2, "0");
		TextOutA(hDC, 210, 460, str1, strlen(str1));
		TextOutA(hDC, 210, 490, str2, strlen(str2));

		_itoa_s(Point_B, str3, 20);
		strcpy_s(str1, "YOU FOOD:");
		strcpy_s(str2, "YOU SCORE:");
		strcat_s(str1, str3);
		strcat_s(str2, str3);
		strcat_s(str2, "0");
		TextOutA(hDC, 210 + GameWindowX_B, 460, str1, strlen(str1));
		TextOutA(hDC, 210 + GameWindowX_B, 490, str2, strlen(str2));
		EndPaint(hDlg, &PtStr);
		int Left, Right;
		if (Point_A > Point_B) {
			Left = IDB_SMILE;
			Right = IDB_CRY;
		}
		else if (Point_A < Point_B) {
			Left = IDB_CRY;
			Right = IDB_SMILE;
		}
		else {
			Left = IDB_SMILE;
			Right = IDB_SMILE;
		}
		hCtrlBlock = GetDlgItem(hDlg, IDC_PAINTA);
		Backgroundpaste(hCtrlBlock, Left, -10, 0);
		hCtrlBlock = GetDlgItem(hDlg, IDC_PAINTB);
		Backgroundpaste(hCtrlBlock, Right, 15, 0);
		PostMessage(hDlg, WM_TIMER, wParam, lParam);
	}
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_OK || LOWORD(wParam) == IDCANCEL) {
			PostMessage(hDlg, WM_CLOSE, wParam, lParam);
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		break;
	}
	return (INT_PTR)FALSE;
}