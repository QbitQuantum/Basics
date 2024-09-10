	LRESULT RichEdit::ParentWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, 
		UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
		if(msg==WM_NOTIFY && (((LPNMHDR)lParam)->code)== EN_LINK) {
			ENLINK* enLinkInfo = (ENLINK *)lParam;
			if(enLinkInfo->msg == WM_LBUTTONUP || enLinkInfo->msg == WM_RBUTTONUP) {
				LONG utlBeg = enLinkInfo->chrg.cpMin;
				LONG utlEnd = enLinkInfo->chrg.cpMax;
				if(utlEnd - utlBeg > 0) {
					HWND hRichEdit = enLinkInfo->nmhdr.hwndFrom;
					wchar_t* urlString = new wchar_t[utlEnd-utlBeg+1];
					SendMessageW(hRichEdit, EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&enLinkInfo->chrg));
					SendMessageW(hRichEdit, EM_GETSELTEXT, 0, reinterpret_cast<LPARAM>(urlString));
					switch(enLinkInfo->msg) {
					case WM_LBUTTONUP:
						ShellExecuteW(NULL, L"open", urlString, NULL, NULL, SW_SHOWNORMAL);
						break;
					case WM_RBUTTONUP:
						copyToClipboard(hRichEdit, urlString);
						break;
					}
					delete [] urlString;
					SendMessage(hRichEdit, EM_SETSEL, utlEnd, utlEnd);
					HideCaret(hRichEdit);
				}
			}
		}
		return DefSubclassProc(hWnd, msg, wParam, lParam);
	}