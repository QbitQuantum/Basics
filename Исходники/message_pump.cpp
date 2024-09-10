INT_PTR ShowTip(WPARAM wParam, LPARAM lParam) {
	CLCINFOTIP *clcit = (CLCINFOTIP *)lParam;
	if(clcit->isGroup) return 0; // no group tips (since they're pretty useless)
	if(clcit->isTreeFocused == 0 && options.show_no_focus == false) return 0;

	CLCINFOTIPEX *clcit2 = (CLCINFOTIPEX *)malloc(sizeof(CLCINFOTIPEX));
	memcpy(clcit2, clcit, sizeof(CLCINFOTIP));
	clcit2->cbSize = sizeof(CLCINFOTIPEX);
	clcit2->proto = 0;
	clcit2->text = 0;

	if(wParam) { // wParam is char pointer containing text - e.g. status bar tooltip
		clcit2->text = a2t((char *)wParam);
		GetCursorPos(&clcit2->ptCursor);

		//MessageBox(0, clcit2->text, _T("ShowTip"), MB_OK);
	}

	PostMPMessage(MUM_CREATEPOPUP, 0, (LPARAM)clcit2);
	return 1;
}