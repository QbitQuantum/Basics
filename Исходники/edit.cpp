LRESULT C_Edit::OnDrop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	try {

		IDataObject* pdto = *reinterpret_cast<IDataObject**>(lParam);

		if (pdto) {

			HRESULT hres = E_FAIL;
			FORMATETC fmte = {CF_HDROP, NULL, DVASPECT_CONTENT, -1,	TYMED_HGLOBAL};
			STGMEDIUM medium;
			int files = 0;

			if (pdto && SUCCEEDED (pdto->GetData(&fmte, &medium))) {

				//char szFileDropped [MAX_PATH];

				files = DragQueryFile((HDROP)medium.hGlobal, 0xFFFFFFFF, NULL, 0);
			}

			OleSetClipboard(pdto);
			OleFlushClipboard();

			C_ClipboardPtr clipboard;

			clipboard.Create();
			
			if (clipboard) {

				if (0 == files) {

					clipboard->Load(CF_TEXT);

					short s = -1;
					clipboard->get_Type(&s);

					switch (s) {
					case CF_OEMTEXT:
					case CF_TEXT:

						BSTR bs = NULL;
						clipboard->get_Text(&bs);
						
						String s(bs);
						
						String::FreeBSTR(&bs);

						int len = s.GetLength();

						SetFocus();

						TCHAR t[1024];
						SendMessage(WM_GETTEXT, 1023, reinterpret_cast<LPARAM>(t));
						String old(t);

						POINT p = { 
							reinterpret_cast<POINT*>(wParam)->x, 
							reinterpret_cast<POINT*>(wParam)->y 
						};
						ScreenToClient(&p);

						int selpos = LOWORD(SendMessage(EM_CHARFROMPOS, 0, MAKELPARAM(p.x, p.y)));

						if (selpos >= 0 && selpos < old.GetLength()) {
							s = old.Left(selpos) + s + old.Right(old.GetLength() - selpos);
						}

						if (selpos < m_dwSelEnd) {

							m_dwSelStart += len;
							m_dwSelEnd += len;
						}

						SendMessage(WM_SETTEXT, 0, reinterpret_cast<LPARAM>(s.toLPCTSTR()));
						SendMessage(EM_SETSEL, selpos, selpos + len);
					}
				}
			}
		}

		OnDragLeave(uMsg, wParam, lParam, bHandled);
	}
	catch (C_STLNonStackException const &exception) {
		exception.Log(_T("Exception in C_Edit::OnCanDrop"));
	}

	return S_OK;
}