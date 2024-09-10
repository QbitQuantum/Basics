/* ----------------------------------------------------------------
    Win\Gui\Window C API
------------------------------------------------------------------*/
int wingui_control_static_autosize(HWND handle, int style, int extrastyle, int x, int y TSRMLS_DC)
{
	HDC dc;
	RECT rect;
	BOOL worked;
	UINT flags = DT_CALCRECT;

	dc = GetDC(handle);
	if (dc == 0) {
		goto error;
	}

	worked = GetClientRect(handle, &rect);

	if (worked == 0) {
		goto error;
	}

	/* get our flags right for drawtext */
	if ((SS_CENTER & style) == SS_CENTER) {
		flags |= DT_CENTER;
	} else if ((SS_RIGHT & style) == SS_RIGHT) {
		flags |= DT_RIGHT;
	} else if ((SS_LEFT & style) == SS_LEFT) {
		flags |= DT_LEFT;
	}
	
	if ( ((WS_EX_RTLREADING & extrastyle) == WS_EX_RTLREADING)
		|| ((WS_EX_LAYOUTRTL & extrastyle) == WS_EX_LAYOUTRTL) ) {
			flags |= DT_RTLREADING;
	}

	if ((SS_WORDELLIPSIS & style) == SS_WORDELLIPSIS) {
		flags |= DT_WORD_ELLIPSIS | DT_SINGLELINE;
	} else if ((SS_PATHELLIPSIS & style) == SS_PATHELLIPSIS) {
		flags |= DT_PATH_ELLIPSIS | DT_SINGLELINE;
	} else if ((SS_ENDELLIPSIS & style) == SS_ENDELLIPSIS) {
		flags |= DT_END_ELLIPSIS | DT_SINGLELINE;
	} 

	if ((SS_NOPREFIX & style) == SS_NOPREFIX) {
		flags |= DT_NOPREFIX;
	} 

	if ((SS_LEFTNOWORDWRAP & style) == SS_LEFTNOWORDWRAP) {
		flags |= DT_SINGLELINE;
	} else if ((SS_SIMPLE & style) == SS_SIMPLE) {
		flags |= DT_SINGLELINE;
	} else {
		flags |= DT_WORDBREAK;
	}

	if ((SS_EDITCONTROL & style) == SS_EDITCONTROL) {
		flags |= DT_EDITCONTROL;
	}

	if (IsWindowUnicode(handle)) {
		int length, worked_len;
		wchar_t * text;

		length = GetWindowTextLengthW(handle);
		text = safe_emalloc(length, sizeof(wchar_t), 1);

		worked_len = GetWindowTextW(handle, text, length + 1);
		if (worked_len == 0) {
			goto error;
		}

		worked = DrawTextW(dc, text, -1, &rect, flags); 

		if (worked == 0) {
			goto error;
		}
	} else {
		int length, worked_len;
		char * text;

		length = GetWindowTextLengthA(handle);
		text = safe_emalloc(length, sizeof(char), 1);

		worked_len = GetWindowTextA(handle, text, length + 1);
		if (worked_len == 0) {
			goto error;
		}

		worked = DrawTextA(dc, text, -1, &rect, flags); 

		if (worked == 0) {
			goto error;
		}
	}

    MoveWindow(handle, x, y, (rect.right - rect.left), (rect.bottom - rect.top), FALSE);
	ReleaseDC(handle, dc);
	return SUCCESS;

error:
	ReleaseDC(handle, dc);
	winsystem_create_error(GetLastError(), ce_winsystem_runtimeexception TSRMLS_CC);
	return FAILURE;
}