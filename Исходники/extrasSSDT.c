/*
* SdtSaveListToFile
*
* Purpose:
*
* Dump table to the selected file
*
*/
VOID SdtSaveListToFile(
	_In_ HWND hwndDlg
	)
{
	
	WCHAR ch;
	INT BufferSize = 0;
	INT	numitems;
	INT	row, subitem;
	SIZE_T sz, k;
	LPWSTR pItem = NULL;
	HCURSOR hSaveCursor;
	HCURSOR hHourGlass;
	WCHAR szTempBuffer[MAX_PATH + 1];

	RtlSecureZeroMemory(szTempBuffer, sizeof(szTempBuffer));

	_strcpy(szTempBuffer, TEXT("list.txt"));
	if (supSaveDialogExecute(hwndDlg, (LPWSTR)&szTempBuffer, TEXT("Text files\0*.txt\0\0"))) {

		hHourGlass = LoadCursorW(NULL, IDC_WAIT);

		ch = (WCHAR)0xFEFF;
		supWriteBufferToFile(szTempBuffer, &ch, sizeof(WCHAR), FALSE, FALSE);

		SetCapture(hwndDlg);
		hSaveCursor = SetCursor(hHourGlass);

		numitems = ListView_GetItemCount(SdtDlgContext.ListView);
		for (row = 0; row < numitems; row++) {

			output[0] = 0;
			for (subitem = 0; subitem < SdtDlgContext.lvColumnCount; subitem++) {

				sz = 0;
				pItem = supGetItemText(SdtDlgContext.ListView, row, subitem, &sz);
				if (pItem) {
					_strcat(output, pItem);
					HeapFree(GetProcessHeap(), 0, pItem);
				}
				if (subitem == 1) {
					for (k = 54; k > sz / sizeof(WCHAR); k--) {
						_strcat(output, TEXT(" "));
					}
				}
				else {
					_strcat(output, TEXT("\t"));
				}
			}
			_strcat(output, L"\r\n");
			BufferSize = (INT)_strlen(output);
			supWriteBufferToFile(szTempBuffer, output, BufferSize * sizeof(WCHAR), FALSE, TRUE);
		}

		SetCursor(hSaveCursor);
		ReleaseCapture();
	}
}