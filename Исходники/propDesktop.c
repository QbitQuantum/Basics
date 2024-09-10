/*
* DesktopListCreate
*
* Purpose:
*
* Initialize listview for desktop list.
* Called once.
*
*/
VOID DesktopListCreate(
	_In_ HWND hwndDlg
	)
{
	LVCOLUMNW	col;
	HANDLE		tmpb;

	DesktopList = GetDlgItem(hwndDlg, ID_DESKTOPSLIST);
	if (DesktopList == NULL)
		return;

	DesktopImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 8, 8);
	if (DesktopImageList) {

		//desktop image
		tmpb = LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_ICON_DESKTOP), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
		if (tmpb) {
			ImageList_ReplaceIcon(DesktopImageList, -1, tmpb);
			DestroyIcon(tmpb);
		}

		//sort images
		tmpb = LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_ICON_SORTUP), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
		if (tmpb) {
			ImageList_ReplaceIcon(DesktopImageList, -1, tmpb);
			DestroyIcon(tmpb);
		}
		tmpb = LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_ICON_SORTDOWN), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
		if (tmpb) {
			ImageList_ReplaceIcon(DesktopImageList, -1, tmpb);
			DestroyIcon(tmpb);
		}

		ListView_SetImageList(DesktopList, DesktopImageList, LVSIL_SMALL);
	}

	ListView_SetExtendedListViewStyle(DesktopList, 
		LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	RtlSecureZeroMemory(&col, sizeof(col));
	col.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT | LVCF_WIDTH | LVCF_ORDER | LVCF_IMAGE;
	col.iSubItem = 1;
	col.pszText = L"Name";
	col.fmt = LVCFMT_LEFT | LVCFMT_BITMAP_ON_RIGHT;
	col.iOrder = 0;
	col.iImage = 2;
	col.cx = 200;
	ListView_InsertColumn(DesktopList, 1, &col);

	col.iSubItem = 2;
	col.pszText = L"SID";
	col.iOrder = 1;
	col.iImage = -1;
	col.cx = 100;
	ListView_InsertColumn(DesktopList, 2, &col);

	col.iSubItem = 3;
	col.pszText = L"Heap Size";
	col.iOrder = 2;
	col.iImage = -1;
	col.cx = 100;
	ListView_InsertColumn(DesktopList, 3, &col);
}