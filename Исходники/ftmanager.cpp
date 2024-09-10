static INT_PTR CALLBACK FtMgrPageDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct TFtPageData *dat = (struct TFtPageData *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	int i;

	switch (msg) {
	case WM_INITDIALOG:
		{
			// Force scrollbar visibility
			SCROLLINFO si = {0};
			si.cbSize = sizeof(si);
			si.fMask = SIF_DISABLENOSCROLL;
			SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

			dat = (struct TFtPageData *)mir_alloc(sizeof(struct TFtPageData));
			dat->wnds = (struct TLayoutWindowList *)List_Create(0, 1);
			dat->scrollPos = 0;
			dat->runningCount = 0;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)dat);
		}
		break;

	case WM_FT_ADD:
		{
			TLayoutWindowInfo *wnd = (struct TLayoutWindowInfo *)mir_alloc(sizeof(struct TLayoutWindowInfo));
			wnd->hwnd = (HWND)lParam;
			GetWindowRect(wnd->hwnd, &wnd->rc);
			List_Insert((SortedList *)dat->wnds, wnd, dat->wnds->realCount);
			LayoutTransfers(hwnd, dat);
			dat->runningCount++;
			PostMessage(GetParent(hwnd), WM_TIMER, 1, NULL);
		}
		break;

	case WM_FT_RESIZE:
		for (i=0; i < dat->wnds->realCount; ++i)
			if (dat->wnds->items[i]->hwnd == (HWND)lParam) {
				GetWindowRect(dat->wnds->items[i]->hwnd, &dat->wnds->items[i]->rc);
				break;
			}
		LayoutTransfers(hwnd, dat);
		break;

	case WM_FT_REMOVE:
		for (i=0; i < dat->wnds->realCount; ++i)
			if (dat->wnds->items[i]->hwnd == (HWND)lParam) {
				mir_free(dat->wnds->items[i]);
				List_Remove((SortedList *)dat->wnds, i);
				break;
			}
		LayoutTransfers(hwnd, dat);
		break;

	case WM_FT_COMPLETED:
		//wParam: { ACKRESULT_SUCCESS | ACKRESULT_FAILED | ACKRESULT_DENIED }
		dat->runningCount--;
		for (i=0; i < dat->wnds->realCount; i++) {
			// no error when canceling (WM_FT_REMOVE is send first, check if hwnd is still registered)
			if (dat->wnds->items[i]->hwnd == (HWND)lParam) {
				SendMessage(GetParent(hwnd), WM_TIMER, 1, (LPARAM)wParam);
				break;
			}
		}
		if (i == dat->wnds->realCount)
			PostMessage(GetParent(hwnd), WM_TIMER, 1, NULL);

		if(dat->runningCount == 0 && (int)wParam == ACKRESULT_SUCCESS && db_get_b(NULL, "SRFile", "AutoClose", 0))
			ShowWindow(hwndFtMgr, SW_HIDE);
		break;

	case WM_FT_CLEANUP:
		for (i=0; i < dat->wnds->realCount; ++i)
			SendMessage(dat->wnds->items[i]->hwnd, WM_FT_CLEANUP, wParam, lParam);
		break;

	case WM_SIZE:
		LayoutTransfers(hwnd, dat);
		break;

	case WM_MOUSEWHEEL:
		{
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (zDelta) {
				int nScrollLines = 0;
				SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, (void*)&nScrollLines, 0);
				for (i=0; i < (nScrollLines + 1) / 2; i++)
					SendMessage(hwnd, WM_VSCROLL, (zDelta < 0) ? SB_LINEDOWN : SB_LINEUP, 0);
			}

			SetWindowLongPtr(hwnd, DWLP_MSGRESULT, 0);
			return TRUE;
		}

	case WM_VSCROLL:
		{
			int pos = dat->scrollPos;
			switch (LOWORD(wParam)) {
			case SB_LINEDOWN:
				pos += 15;
				break;
			case SB_LINEUP:
				pos -= 15;
				break;
			case SB_PAGEDOWN:
				pos += dat->height - 10;
				break;
			case SB_PAGEUP:
				pos -= dat->height - 10;
				break;
			case SB_THUMBTRACK:
				pos = HIWORD(wParam);
				break;
			}

			if (pos > dat->dataHeight - dat->height) pos = dat->dataHeight - dat->height;
			if (pos < 0) pos = 0;

			if (dat->scrollPos != pos) {
				ScrollWindow(hwnd, 0, dat->scrollPos - pos, NULL, NULL);
				SetScrollPos(hwnd, SB_VERT, pos, TRUE);
				dat->scrollPos = pos;
			}
			break;
		}

	case M_PRESHUTDOWN:
		for (i=0; i < dat->wnds->realCount; ++i)
			PostMessage(dat->wnds->items[i]->hwnd, WM_COMMAND, MAKEWPARAM(IDCANCEL, BN_CLICKED), 0);
		break;

	case M_CALCPROGRESS:
		{
			TFtProgressData *prg = (TFtProgressData *)wParam;
			for (i=0; i < dat->wnds->realCount; ++i) {
				struct FileDlgData *trdat = (struct FileDlgData *)GetWindowLongPtr(dat->wnds->items[i]->hwnd, GWLP_USERDATA);
				if (trdat->transferStatus.totalBytes && trdat->fs && !trdat->send && (trdat->transferStatus.totalBytes == trdat->transferStatus.totalProgress))
					prg->scan++;
				else if (trdat->transferStatus.totalBytes && trdat->fs) { // in progress
					prg->run++;
					prg->totalBytes += trdat->transferStatus.totalBytes;
					prg->totalProgress += trdat->transferStatus.totalProgress;
				}
				else if (trdat->fs) // starting
					prg->init++;
			}
		}
		break;

	case WM_DESTROY:
		for (i=0; i < dat->wnds->realCount; ++i)
			mir_free(dat->wnds->items[i]);
		List_Destroy((SortedList *)dat->wnds);
		mir_free(dat->wnds);
		mir_free(dat);
		break;
	}

	return FALSE;
}