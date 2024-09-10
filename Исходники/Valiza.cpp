INT_PTR CALLBACK Raspuns(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HBITMAP bmp1;///////////
	//HBITMAP bmp2;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{


	case WM_INITDIALOG:{
						   ////GetDlgItem(hDlg, IDC_EDIT1)
						   
						   //HBITMAP hImage = (HBITMAP)LoadImage(NULL, L"cumsejoaca.bmp", IMAGE_BITMAP, 500, 460, LR_LOADFROMFILE);
						   //HWND hImageView = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 0, 500, 600, hDlg, (HMENU)IMAGE_VIEW, GetModuleHandle(NULL), NULL);
						   //SendMessage(hImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
						  // SendMessage(GetDlgItem(hDlg, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)string2);
					//lista de cuvinte corecte
						   FILE *fin = fopen("date.txt", "r");
						   while (!feof(fin)){
							   fwscanf(fin, L"%ls", string2);
							   SendMessage(GetDlgItem(hDlg, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)string2);
						   }
						   fclose(fin);
					//lista de cuvinte corecte_end
						   return (INT_PTR)TRUE;

	}break;



	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//SetFocus(HWND(IDOK1))
			//SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), L"MIHAI");
			//SetWindowText(GetDlgItem(hDlg, IDC_EDIT3), L"MIHAI noifacnonuac uiea u avuohouc houa \\n petre midhaifean ofieanoifnaoincofa oinceaonf ocuanuoeacwonu iu bciua icgeiag ieagiyb diya ydivayvdiyaw vdyiaw vyidva wyivdywie vyiawdv yiwv yid waviyvd ayis vyid vayid vweiy vyidav siydv aiywev aiywe v");
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}