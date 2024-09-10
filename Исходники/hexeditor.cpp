LRESULT CALLBACK HexEditorProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT r;
//	RECT r2;
	PAINTSTRUCT ps;
	SCROLLINFO si;
//	int dx1, dy1, dx2, dy2;
//	static int watchIndex=0;

	switch(uMsg)
	{
		case WM_CREATE:
		{
			HexDC = GetDC(hDlg);
			SelectObject(HexDC, HexFont);
			SetTextAlign(HexDC, TA_UPDATECP | TA_TOP | TA_LEFT);
			
			if (Full_Screen)
			{
				while (ShowCursor(false) >= 0);
				while (ShowCursor(true) < 0);
			}

			GetWindowRect(HWnd, &r);
			Hex.DialogPosX = r.right;
			Hex.DialogPosY = r.top;

			SetWindowPos(
				hDlg,
				NULL,
				Hex.DialogPosX,
				Hex.DialogPosY,
				Hex.DialogSizeX,
				Hex.DialogSizeY,
				SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_SHOWWINDOW
			);
			
			ZeroMemory(&si, sizeof(SCROLLINFO));
			si.cbSize = sizeof(si);
			si.fMask  = SIF_RANGE | SIF_PAGE;
			si.nMin   = 0;
			si.nMax   = _68K_RAM_SIZE / 16;
			si.nPage  = 16;
			SetScrollInfo(hDlg, SB_VERT, &si, TRUE);
			return 0;
		}
		break;
/*
		case WM_COMMAND:
		{
			switch(wParam)
			{
			case IDC_SAVE:
				{
				char fname[2048];
				strcpy(fname,"dump.bin");
				if(Change_File_S(fname,".","Save Full Dump As...","All Files\0*.*\0\0","*.*",hDlg))
				{
					FILE *out=fopen(fname,"wb+");
					int i;
					for (i=0;i<sizeof(Ram_68k);++i)
					{
						fname[i&2047]=Ram_68k[i^1];
						if ((i&2047)==2047)
							fwrite(fname,1,sizeof(fname),out);
					}
					fwrite(fname,1,i&2047,out);
					fclose(out);
				}
				}
				break;

			case IDC_BUTTON1:
				{
				char fname[2048];
				GetDlgItemText(hDlg,IDC_EDIT1,fname,2047);
				int CurPos;
				if ((strnicmp(fname,"ff",2)==0) && sscanf(fname+2,"%x",&CurPos))
				{
					SetScrollPos(GetDlgItem(hDlg,IDC_SCROLLBAR1),SB_CTL,(CurPos>>4),TRUE);
					Update_RAM_Dump();
				}
				}
				break;
			}
		}	break;
*/
		case WM_VSCROLL:
		{
			ZeroMemory(&si, sizeof(SCROLLINFO));
			si.fMask = SIF_ALL;
			si.cbSize = sizeof(SCROLLINFO);
			GetScrollInfo(hDlg,SB_VERT,&si);

			switch(LOWORD(wParam))
			{
				case SB_ENDSCROLL:
				case SB_TOP:
				case SB_BOTTOM:
					break;
				case SB_LINEUP:
					si.nPos--;
					break;
				case SB_LINEDOWN:
					si.nPos++;
					break;
				case SB_PAGEUP:
					si.nPos -= si.nPage;
					break;
				case SB_PAGEDOWN:
					si.nPos += si.nPage;
					break;
				case SB_THUMBPOSITION:
				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
					break;
			}
			if (si.nPos < si.nMin)
				si.nPos = si.nMin;
			if ((si.nPos + (int) si.nPage) > si.nMax)
				si.nPos = si.nMax - si.nPage;

			Hex.OffsetVisibleFirst = si.nPos * 16;
			SetScrollInfo(hDlg, SB_VERT, &si, TRUE);
			UpdateHexEditor();
			return 0;
		}
		break;

		case WM_MOUSEWHEEL:
		{
			int WheelDelta = (short) HIWORD(wParam);

			ZeroMemory(&si, sizeof(SCROLLINFO));
			si.fMask  = SIF_ALL;
			si.cbSize = sizeof(SCROLLINFO);
			GetScrollInfo(hDlg, SB_VERT, &si);

			if (WheelDelta < 0)
				si.nPos += si.nPage;
			if (WheelDelta > 0)
				si.nPos -= si.nPage;
			if (si.nPos < si.nMin)
				si.nPos = si.nMin;
			if ((si.nPos + (int) si.nPage) > si.nMax)
				si.nPos = si.nMax - si.nPage;

			Hex.OffsetVisibleFirst = si.nPos*16;
			SetScrollInfo(hDlg,SB_VERT,&si,TRUE);
			UpdateHexEditor();
			return 0;
		}
		break;

		case WM_PAINT:
		{
			BeginPaint(hDlg, &ps);			
			static char buf[10];
			int row = 0, line = 0;

			// TOP HEADER, static.
			for (row = 0; row < 16; row++)
			{
				MoveToEx(HexDC, row * Hex.CellWidth + Hex.GapHeaderH, 0, NULL);
				SetBkColor(HexDC, Hex.ColorBG);
				SetTextColor(HexDC, Hex.ColorFont);
				sprintf(buf, "%2X", row);
				TextOut(HexDC, 0, 0, buf, strlen(buf));					
			}

			// LEFT HEADER, semi-dynamic.
			for (line = 0; line < 16; line++)
			{
				MoveToEx(HexDC, 0, line * Hex.CellHeight + Hex.GapHeaderV, NULL);
				SetBkColor(HexDC, Hex.ColorBG);
				SetTextColor(HexDC, Hex.ColorFont);
				sprintf(buf, "%06X:", Hex.OffsetVisibleFirst + line*16 + Hex.MemoryRegion);
				TextOut(HexDC, 0, 0, buf, strlen(buf));
			}

			// RAM, dynamic.
			for (line = 0; line < 16; line++)
			{
				for (row = 0; row < 16; row++)
				{
					MoveToEx(HexDC, row * Hex.CellWidth + Hex.GapHeaderH, line * Hex.CellHeight + Hex.GapHeaderV, NULL);
					sprintf(buf, "%02X", (int) Ram_68k[Hex.OffsetVisibleFirst + line*16 + row]);
					TextOut(HexDC, 0, 0, buf, strlen(buf));
				}
			}
			EndPaint(hDlg, &ps);
			return 0;
		}
		break;

		case WM_CLOSE:
			if (Full_Screen)
			{
				while (ShowCursor(true) < 0);
				while (ShowCursor(false) >= 0);
			}
			KillHexEditor();
			return 0;
	}
	return DefWindowProc(hDlg, uMsg, wParam, lParam);
}