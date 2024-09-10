int FAR PASCAL
DialogVector2D(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 
 char *strbuffer;
 Vector2D *vtemp;
 
 switch (message)
	{
		case WM_INITDIALOG:
			strbuffer=new char[20];
			vtemp=(Vector2D *)(CT_data);
			strbuffer=gcvt((double)(vtemp->x),3,strbuffer);
            SetDlgItemText(hWnd,IDC_EDIT1,strbuffer);
			strbuffer=gcvt((double)(vtemp->y),3,strbuffer);
            SetDlgItemText(hWnd,IDC_EDIT2,strbuffer);

			SetDlgItemInt(hWnd,IDC_STATICN,CT_keynum,false);
			SetDlgItemInt(hWnd,IDC_STATICM,CT_keypos,false);
			delete [] strbuffer;

			SetFocus(GetDlgItem(hWnd,IDC_EDIT1));
			PostMessage(GetDlgItem(hWnd,IDC_EDIT1),EM_SETSEL,0,10);

			return FALSE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) 
			{
				strbuffer=new char[20];
				GetDlgItemText(hWnd,IDC_EDIT1,strbuffer,20);
				vtemp=(Vector2D *)CT_data;
				vtemp->x=(float)atof(strbuffer);
				GetDlgItemText(hWnd,IDC_EDIT2,strbuffer,20);
				vtemp->y=(float)atof(strbuffer);
				delete [] strbuffer;
				EndDialog(hWnd, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hWnd, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}