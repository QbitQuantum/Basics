BOOL CALLBACK NavDialog::run_dlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	long yPos;
    int LineStart;
    int LineVisible;
    int Delta;

	switch (Message) 
	{
		case WM_INITDIALOG:
		{
            // Here, I modify window styles (set H and V redraw)
            SetClassLong(hWnd, GCL_STYLE, CS_HREDRAW | CS_VREDRAW);
            m_hWnd = hWnd;
            ReadyToDraw = FALSE;
    		break;
		}

	    case WM_PAINT:
		{
            ReadyToDraw = TRUE;
            return OnPaint(hWnd);
		}

		case WM_NOTIFY:
		{
			//return DockingDlgInterface::run_dlgProc(hWnd, Message, wParam, lParam);
			break;
		}

		case WM_DESTROY:
		{
            // Delete objects
            DeleteDC(m_hMemDC1);
            DeleteDC(m_hMemDC2);
            DeleteDC(m_hMemDCView);
            DeleteObject(m_hMemBMP1);
            DeleteObject(m_hMemBMP2);
            DeleteObject(m_hMemBMPView);

            PostQuitMessage(0); 
			break;
		}

        case WM_LBUTTONDOWN:
            POINT pt;
            SetCapture(hWnd);
            yPos = HIWORD(lParam);
            current_line = yPos * m_ScaleFactor;
            LineVisible = SendMessageA(_nppData._scintillaMainHandle, SCI_LINESONSCREEN, 0, 0);
            LineStart = SendMessageA(_nppData._scintillaMainHandle, SCI_GETFIRSTVISIBLELINE, 0, 0);
            Delta = current_line - LineVisible/2 - LineStart;
            SendMessageA(_nppData._scintillaMainHandle, SCI_LINESCROLL, 0, (LPARAM)Delta);
            SendMessageA(_nppData._scintillaMainHandle, SCI_GOTOLINE, (WPARAM)current_line, 0);
            break;

        case WM_LBUTTONUP:
            ReleaseCapture();
            break;

        case WM_MOUSEMOVE:
            long start;
			long next_line;
            int LineStart;
            int LineVisible;
            if (GetCapture() == hWnd) 
            { 
                yPos = HIWORD(lParam);
                next_line = yPos * m_ScaleFactor;
				Delta = next_line - current_line;
				SendMessageA(_nppData._scintillaMainHandle, SCI_LINESCROLL, 0, (LPARAM)Delta);
				SendMessageA(_nppData._scintillaMainHandle, SCI_GOTOLINE, (WPARAM)next_line, 0);
				current_line = next_line;
            }
            break;

		default:
			return DockingDlgInterface::run_dlgProc(hWnd, Message, wParam, lParam);
	}

	return FALSE;
}