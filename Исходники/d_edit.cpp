static void editdata_str_to_bytes(EDITDATA *ed, HWND hWnd, int item)	{

	GetDlgItemTextW(hWnd, item, ed->str, MAX_EDIT_STR);
	if(ed->codepage)	{
		// excluding the terminating null character
		ed->bytes_len = WideCharToMultiByte(ed->codepage, 0, ed->str, -1, (LPSTR)ed->bytes, MAX_EDIT_STR * 3, NULL, NULL) - 1;
	} else {
		ed->bytes_len = milstr_solveHEXbuffer(ed->bytes, MAX_EDIT_STR, ed->str);
	}
}