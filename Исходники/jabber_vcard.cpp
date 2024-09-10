static INT_PTR CALLBACK PhotoDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const unsigned long iPageId = 3;

	TCHAR szAvatarFileName[MAX_PATH], szTempPath[MAX_PATH], szTempFileName[MAX_PATH];
	PhotoDlgProcData* dat = (PhotoDlgProcData*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

	switch (msg) {
	case WM_INITDIALOG:
		if (!lParam) break; // Launched from userinfo
		TranslateDialogDefault(hwndDlg);
		SendDlgItemMessage(hwndDlg, IDC_LOAD, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(hInst, MAKEINTRESOURCE(IDI_OPEN), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0));
		SendDlgItemMessage(hwndDlg, IDC_LOAD, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_DELETE, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadImage(hInst, MAKEINTRESOURCE(IDI_DELETE), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0));
		SendDlgItemMessage(hwndDlg, IDC_DELETE, BUTTONSETASFLATBTN, TRUE, 0);
		ShowWindow(GetDlgItem(hwndDlg, IDC_SAVE), SW_HIDE);
		{
			dat = new PhotoDlgProcData;
			dat->ppro = (CJabberProto*)lParam;
			dat->hBitmap = NULL;
			dat->ppro->m_bPhotoChanged = FALSE;
			SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)dat);
			dat->ppro->WindowSubscribe(hwndDlg);
		}
		SendMessage(hwndDlg, WM_JABBER_REFRESH_VCARD, 0, 0);
		break;

	case WM_JABBER_REFRESH_VCARD:
		if (dat->hBitmap) {
			DeleteObject(dat->hBitmap);
			dat->hBitmap = NULL;
			DeleteFile(dat->ppro->m_szPhotoFileName);
			dat->ppro->m_szPhotoFileName[0] = '\0';
		}
		EnableWindow(GetDlgItem(hwndDlg, IDC_DELETE), FALSE);
		dat->ppro->GetAvatarFileName(NULL, szAvatarFileName, _countof(szAvatarFileName));
		if (_taccess(szAvatarFileName, 0) == 0) {
			if (GetTempPath(_countof(szTempPath), szTempPath) <= 0)
				mir_tstrcpy(szTempPath, _T(".\\"));
			if (GetTempFileName(szTempPath, _T("jab"), 0, szTempFileName) > 0) {
				dat->ppro->debugLog(_T("Temp file = %s"), szTempFileName);
				if (CopyFile(szAvatarFileName, szTempFileName, FALSE) == TRUE) {
					if ((dat->hBitmap = Bitmap_Load(szTempFileName)) != NULL) {
						FIP->FI_Premultiply(dat->hBitmap);
						mir_tstrcpy(dat->ppro->m_szPhotoFileName, szTempFileName);
						EnableWindow(GetDlgItem(hwndDlg, IDC_DELETE), TRUE);
					}
					else DeleteFile(szTempFileName);
				}
				else DeleteFile(szTempFileName);
			}
		}

		dat->ppro->m_bPhotoChanged = FALSE;
		InvalidateRect(hwndDlg, NULL, TRUE);
		UpdateWindow(hwndDlg);
		break;

	case WM_JABBER_CHANGED:
		dat->ppro->SetServerVcard(dat->ppro->m_bPhotoChanged, dat->ppro->m_szPhotoFileName);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_DELETE:
			if (dat->hBitmap) {
				DeleteObject(dat->hBitmap);
				dat->hBitmap = NULL;
				DeleteFile(dat->ppro->m_szPhotoFileName);
				dat->ppro->m_szPhotoFileName[0] = '\0';
				dat->ppro->m_bPhotoChanged = TRUE;
				EnableWindow(GetDlgItem(hwndDlg, IDC_DELETE), FALSE);
				InvalidateRect(hwndDlg, NULL, TRUE);
				UpdateWindow(hwndDlg);
				dat->ppro->m_vCardUpdates |= (1UL << iPageId);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
			}
			break;

		case IDC_LOAD:
			TCHAR szFilter[512], szFileName[MAX_PATH];
			Bitmap_GetFilter(szFilter, _countof(szFilter));

			OPENFILENAME ofn = { 0 };
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwndDlg;
			ofn.lpstrFilter = szFilter;
			ofn.lpstrCustomFilter = NULL;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_DONTADDTORECENT;
			szFileName[0] = '\0';
			if (GetOpenFileName(&ofn)) {
				struct _stat st;
				HBITMAP hNewBitmap;

				dat->ppro->debugLog(_T("File selected is %s"), szFileName);
				if (_tstat(szFileName, &st) < 0 || st.st_size > 40 * 1024) {
					MessageBox(hwndDlg, TranslateT("Only JPG, GIF, and BMP image files smaller than 40 KB are supported."), TranslateT("Jabber vCard"), MB_OK | MB_SETFOREGROUND);
					break;
				}
				if (GetTempPath(_countof(szTempPath), szTempPath) <= 0)
					mir_tstrcpy(szTempPath, _T(".\\"));
				
				if (GetTempFileName(szTempPath, _T("jab"), 0, szTempFileName) > 0) {
					dat->ppro->debugLog(_T("Temp file = %s"), szTempFileName);
					if (CopyFile(szFileName, szTempFileName, FALSE) == TRUE) {
						if ((hNewBitmap = Bitmap_Load(szTempFileName)) != NULL) {
							if (dat->hBitmap) {
								DeleteObject(dat->hBitmap);
								DeleteFile(dat->ppro->m_szPhotoFileName);
							}

							dat->hBitmap = hNewBitmap;
							mir_tstrcpy(dat->ppro->m_szPhotoFileName, szTempFileName);
							dat->ppro->m_bPhotoChanged = TRUE;
							EnableWindow(GetDlgItem(hwndDlg, IDC_DELETE), TRUE);
							InvalidateRect(hwndDlg, NULL, TRUE);
							UpdateWindow(hwndDlg);
							dat->ppro->m_vCardUpdates |= (1UL << iPageId);
							SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
						}
						else DeleteFile(szTempFileName);
					}
					else DeleteFile(szTempFileName);
				}
			}
			break;
		}
		break;

	case WM_PAINT:
		if (dat->hBitmap) {
			BITMAP bm;
			POINT ptSize, ptOrg, pt, ptFitSize;
			RECT rect;

			HWND hwndCanvas = GetDlgItem(hwndDlg, IDC_CANVAS);
			HDC hdcCanvas = GetDC(hwndCanvas);
			HDC hdcMem = CreateCompatibleDC(hdcCanvas);
			SelectObject(hdcMem, dat->hBitmap);
			SetMapMode(hdcMem, GetMapMode(hdcCanvas));
			GetObject(dat->hBitmap, sizeof(BITMAP), (LPVOID)&bm);
			ptSize.x = bm.bmWidth;
			ptSize.y = bm.bmHeight;
			DPtoLP(hdcCanvas, &ptSize, 1);
			ptOrg.x = ptOrg.y = 0;
			DPtoLP(hdcMem, &ptOrg, 1);
			GetClientRect(hwndCanvas, &rect);
			InvalidateRect(hwndCanvas, NULL, TRUE);
			UpdateWindow(hwndCanvas);
			if (ptSize.x <= rect.right && ptSize.y <= rect.bottom) {
				pt.x = (rect.right - ptSize.x) / 2;
				pt.y = (rect.bottom - ptSize.y) / 2;
				ptFitSize = ptSize;
			}
			else {
				if (((float)(ptSize.x - rect.right)) / ptSize.x > ((float)(ptSize.y - rect.bottom)) / ptSize.y) {
					ptFitSize.x = rect.right;
					ptFitSize.y = (ptSize.y*rect.right) / ptSize.x;
					pt.x = 0;
					pt.y = (rect.bottom - ptFitSize.y) / 2;
				}
				else {
					ptFitSize.x = (ptSize.x*rect.bottom) / ptSize.y;
					ptFitSize.y = rect.bottom;
					pt.x = (rect.right - ptFitSize.x) / 2;
					pt.y = 0;
				}
			}

			RECT rc;
			GetClientRect(hwndCanvas, &rc);
			if (IsThemeActive())
				DrawThemeParentBackground(hwndCanvas, hdcCanvas, &rc);
			else
				FillRect(hdcCanvas, &rc, (HBRUSH)GetSysColorBrush(COLOR_BTNFACE));

			if (bm.bmBitsPixel == 32) {
				BLENDFUNCTION bf = { 0 };
				bf.AlphaFormat = AC_SRC_ALPHA;
				bf.BlendOp = AC_SRC_OVER;
				bf.SourceConstantAlpha = 255;
				GdiAlphaBlend(hdcCanvas, pt.x, pt.y, ptFitSize.x, ptFitSize.y, hdcMem, ptOrg.x, ptOrg.y, ptSize.x, ptSize.y, bf);
			}
			else {
				SetStretchBltMode(hdcCanvas, COLORONCOLOR);
				StretchBlt(hdcCanvas, pt.x, pt.y, ptFitSize.x, ptFitSize.y, hdcMem, ptOrg.x, ptOrg.y, ptSize.x, ptSize.y, SRCCOPY);
			}

			DeleteDC(hdcMem);
		}
		break;

	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->idFrom == 0) {
			switch (((LPNMHDR)lParam)->code) {
			case PSN_PARAMCHANGED:
				SendMessage(hwndDlg, WM_INITDIALOG, 0, ((PSHNOTIFY*)lParam)->lParam);
				break;

			case PSN_APPLY:
				dat->ppro->m_vCardUpdates &= ~(1UL << iPageId);
				dat->ppro->SaveVcardToDB(hwndDlg, iPageId);
				if (!dat->ppro->m_vCardUpdates)
					dat->ppro->SetServerVcard(dat->ppro->m_bPhotoChanged, dat->ppro->m_szPhotoFileName);
				break;
			}
		}
		break;

	case WM_DESTROY:
		DestroyIcon((HICON)SendDlgItemMessage(hwndDlg, IDC_LOAD, BM_SETIMAGE, IMAGE_ICON, 0));
		DestroyIcon((HICON)SendDlgItemMessage(hwndDlg, IDC_DELETE, BM_SETIMAGE, IMAGE_ICON, 0));
		dat->ppro->WindowUnsubscribe(hwndDlg);
		if (dat->hBitmap) {
			dat->ppro->debugLogA("Delete bitmap");
			DeleteObject(dat->hBitmap);
			DeleteFile(dat->ppro->m_szPhotoFileName);
		}
		delete dat;
		break;
	}
	return FALSE;
}