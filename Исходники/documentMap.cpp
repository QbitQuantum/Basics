BOOL CALLBACK DocumentMap::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG :
        {
			HWND hwndScintilla = (HWND)::SendMessage(_hParent, NPPM_CREATESCINTILLAHANDLE, 0, (LPARAM)_hSelf);
			_pScintillaEditView = (ScintillaEditView *)::SendMessage(_hParent, NPPM_INTERNAL_GETSCINTEDTVIEW, 0, (LPARAM)hwndScintilla);
			_pScintillaEditView->execute(SCI_SETZOOM, (WPARAM)-10, 0);
			_pScintillaEditView->execute(SCI_SETVSCROLLBAR, FALSE, 0);
			_pScintillaEditView->execute(SCI_SETHSCROLLBAR, FALSE, 0);

			_pScintillaEditView->showIndentGuideLine(false);
			_pScintillaEditView->display();
			
			reloadMap();

			_vzDlg.init(::GetModuleHandle(NULL), _hSelf);
			_vzDlg.doDialog();
			(NppParameters::getInstance())->SetTransparent(_vzDlg.getHSelf(), 50); // 0 <= transparancy < 256

			setSyntaxLiliting();
			
			_pScintillaEditView->showMargin(0, false);
			_pScintillaEditView->showMargin(1, false);
			_pScintillaEditView->showMargin(2, false);
			_pScintillaEditView->showMargin(3, false);
			
            return TRUE;
        }

        case WM_SIZE:
        {
			if (_pScintillaEditView)
			{
				int width = LOWORD(lParam);
				int height = HIWORD(lParam);

				if (_vzDlg.isCreated())
				{
					POINT pt = {0,0};
					::ClientToScreen(_hSelf, &pt);
					if (!_pScintillaEditView->isWrap())
						::MoveWindow(_pScintillaEditView->getHSelf(), 0, 0, width, height, TRUE);
						
					::MoveWindow(_vzDlg.getHSelf(), pt.x, pt.y, width, height, TRUE);
				}
			}
            break;
        }

		case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code)
			{
				case DMN_CLOSE:
				{
					::SendMessage(_hParent, WM_COMMAND, IDM_VIEW_DOC_MAP, 0);
					return TRUE;
				}

				case DMN_SWITCHIN:
				{
					_vzDlg.display();
					reloadMap();
					return TRUE;
				}

				case DMN_SWITCHOFF:
				{
					_vzDlg.display(false);
					return TRUE;
				}

				case DMN_FLOATDROPPED:
				{
					RECT rc;
					getClientRect(rc);
					int width = rc.right - rc.left;
					int height = rc.bottom - rc.top;

					//RECT scinrc;
					//_pScintillaEditView->getClientRect(scinrc);
					//int scinrcWidth = scinrc.right - scinrc.left;
					//::MoveWindow(_pScintillaEditView->getHSelf(), 0, 0, scinrcWidth, height, TRUE);

					POINT pt = {0,0};
					::ClientToScreen(_hSelf, &pt);
					::MoveWindow(_vzDlg.getHSelf(), pt.x, pt.y, width, height, TRUE);
					scrollMap();
					return TRUE;
				}

				case NM_DBLCLK:
				{
					return TRUE;
				}

				default:
					break;
				
			}
	
		}
		return TRUE;

		case DOCUMENTMAP_SCROLL:
		{
			bool dir = (wParam != 0);
			moveMode mode = (lParam == 0)?perLine:perPage;
			scrollMap(dir, mode);
		}
		return TRUE;

		case DOCUMENTMAP_MOUSECLICKED:
		{
			int newPosY = HIWORD(lParam);
			int currentCenterPosY = _vzDlg.getCurrentCenterPosY();
			int pixelPerLine = _pScintillaEditView->execute(SCI_TEXTHEIGHT, 0); 
			int jumpDistance = newPosY - currentCenterPosY;
			int nbLine2jump = jumpDistance/pixelPerLine;
			(*_ppEditView)->execute(SCI_LINESCROLL, 0, nbLine2jump);

			scrollMap();
		}
		return TRUE;

		case DOCUMENTMAP_MOUSEWHEEL:
		{
			(*_ppEditView)->mouseWheel(wParam, lParam);
		}
		return TRUE;



        default :
            return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
    }
	return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
}