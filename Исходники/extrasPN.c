/*
* PNDlgHandleNotify
*
* Purpose:
*
* WM_NOTIFY processing for PNDialog listview.
*
*/
VOID PNDlgHandleNotify(
	LPNMLISTVIEW	nhdr
	)
{
	LVCOLUMNW		col;
	INT				c, k;

	if (nhdr == NULL)
		return;

	if (nhdr->hdr.idFrom != ID_NAMESPACELIST)
		return;

	switch (nhdr->hdr.code) {


	case LVN_COLUMNCLICK:
		
		PnDlgContext.bInverseSort = !PnDlgContext.bInverseSort;
		PnDlgContext.lvColumnToSort = ((NMLISTVIEW *)nhdr)->iSubItem;
		ListView_SortItemsEx(PnDlgContext.ListView, &PNListCompareFunc, PnDlgContext.lvColumnToSort);

		RtlSecureZeroMemory(&col, sizeof(col));
		col.mask = LVCF_IMAGE;
		col.iImage = -1;

		for (c = 0; c < PnDlgContext.lvColumnCount; c++)
			ListView_SetColumn(PnDlgContext.ListView, c, &col);

		k = ImageList_GetImageCount(ListViewImages);
		if (PnDlgContext.bInverseSort)
			col.iImage = k - 2;
		else
			col.iImage = k - 1;

		ListView_SetColumn(PnDlgContext.ListView, ((NMLISTVIEW *)nhdr)->iSubItem, &col);
		break;

	default:
		break;
	}
}