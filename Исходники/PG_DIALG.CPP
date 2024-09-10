//
//  Page Layout Dialog Box
//
BOOL FAR PASCAL _export PAGE::PageDialog ( HWND hDlg, WORD message, WORD wParam, LONG lParam )
{

	PAGE *page;

	switch ( message )
	{
	case WM_INITDIALOG:
		page = (PAGE*)AObjGetRuntimeInfo((OBJECTID)lParam);
		SetWindowLong(hDlg, DWL_USER, (long)page);
		page->SetDialog(hDlg);
		page->hPen1 = CreatePen(PS_SOLID, 1, 0x00808080L);
		page->hPen2 = CreatePen(PS_SOLID, 2, 0x00808080L);

		page->InitDlgControl();
		AUtlSetTitleFont(OTYPE_PAGE, NULL, GetDlgItem(hDlg, IDD_OBJECT));
		AUtlCenterDialog(hDlg, 0);

		return TRUE;

	case WM_MOVE:
		page = (PAGE*)GetWindowLong(hDlg, DWL_USER);
		GetWindowRect(page->hLayout, &page->layoutRect);
		return 0;

	case WM_COMMAND:
		page = (PAGE*)GetWindowLong(hDlg, DWL_USER);
		switch ( wParam )
		{
		case PAGEOK:
			SetFocus(GetDlgItem(hDlg, PAGEOK));
			page->UpdateObject();
			page->DeleteListData();
			EndDialog(hDlg, 0);
			return TRUE;

		case PAGECANCEL:
			SetFocus(GetDlgItem(hDlg, PAGECANCEL));
			page->DeleteListData();
			EndDialog(hDlg, 0);
			return TRUE;

		case PAGEHELP:
//			WinHelp(hDlg, HELPFILE, HELP_CONTEXT, HELPID_OBJD_Page);
			return TRUE;

		case PAGEADD:
			page->Add();
			return TRUE;

		case PAGEGRID:
			page->snap = IsDlgButtonChecked(hDlg, PAGEGRID);
			return TRUE;

		case PAGEREMOVE:
			page->Remove();
			page->UpdateRemoveButton();
			page->UpdateEditButton();
			return TRUE;

		case PAGEEDIT:
			page->Edit();
			return TRUE;

		case PAGEAVAIL:
			if (HIWORD(lParam) == LBN_SELCHANGE)
				page->UpdateAddButton();

			if (HIWORD(lParam) == LBN_DBLCLK)
				page->Add();
			return TRUE;

		case PAGESELECT:
			if (HIWORD(lParam) == LBN_SELCHANGE)
			{
				page->MakeWindowTop();
				page->UpdateRemoveButton();
				page->UpdateEditButton();
			}

			if (HIWORD(lParam) == LBN_DBLCLK)
				page->Edit();
			return TRUE;
		}
		break;

	case WM_PAINT:
		page = (PAGE*)GetWindowLong(hDlg, DWL_USER);
		page->DrawObjectName();
   	return FALSE;
	}
	return FALSE;
}