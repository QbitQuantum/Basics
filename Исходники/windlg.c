static int CALLBACK LogProc(HWND hwnd, UINT msg,
			    WPARAM wParam, LPARAM lParam)
{
    int i;

    switch (msg) {
      case WM_INITDIALOG:
	{
	    char *str = dupprintf("%s Event Log", appname);
	    SetWindowText(hwnd, str);
	    sfree(str);
	}
	{
	    static int tabs[4] = { 78, 108 };
	    SendDlgItemMessage(hwnd, IDN_LIST, LB_SETTABSTOPS, 2,
			       (LPARAM) tabs);
	}
	for (i = 0; i < nevents; i++)
	    SendDlgItemMessage(hwnd, IDN_LIST, LB_ADDSTRING,
			       0, (LPARAM) events[i]);
	return 1;
      case WM_COMMAND:
	switch (LOWORD(wParam)) {
	  case IDOK:
	  case IDCANCEL:
	    logbox = NULL;
	    SetActiveWindow(GetParent(hwnd));
	    DestroyWindow(hwnd);
	    return 0;
	  case IDN_COPY:
	    if (HIWORD(wParam) == BN_CLICKED ||
		HIWORD(wParam) == BN_DOUBLECLICKED) {
		int selcount;
		int *selitems;
		selcount = SendDlgItemMessage(hwnd, IDN_LIST,
					      LB_GETSELCOUNT, 0, 0);
		if (selcount == 0) {   /* don't even try to copy zero items */
		    MessageBeep(0);
		    break;
		}

		selitems = snewn(selcount, int);
		if (selitems) {
		    int count = SendDlgItemMessage(hwnd, IDN_LIST,
						   LB_GETSELITEMS,
						   selcount,
						   (LPARAM) selitems);
		    int i;
		    int size;
		    char *clipdata;
		    static unsigned char sel_nl[] = SEL_NL;

		    if (count == 0) {  /* can't copy zero stuff */
			MessageBeep(0);
			break;
		    }

		    size = 0;
		    for (i = 0; i < count; i++)
			size +=
			    strlen(events[selitems[i]]) + sizeof(sel_nl);

		    clipdata = snewn(size, char);
		    if (clipdata) {
			char *p = clipdata;
			for (i = 0; i < count; i++) {
			    char *q = events[selitems[i]];
			    int qlen = strlen(q);
			    memcpy(p, q, qlen);
			    p += qlen;
			    memcpy(p, sel_nl, sizeof(sel_nl));
			    p += sizeof(sel_nl);
			}
			write_aclip(NULL, clipdata, size, TRUE);
			sfree(clipdata);
		    }
		    sfree(selitems);

		    for (i = 0; i < nevents; i++)
			SendDlgItemMessage(hwnd, IDN_LIST, LB_SETSEL,
					   FALSE, i);
		}
	    }
	    return 0;
	}
	return 0;
      case WM_CLOSE:
	logbox = NULL;
	SetActiveWindow(GetParent(hwnd));
	DestroyWindow(hwnd);
	return 0;
    }