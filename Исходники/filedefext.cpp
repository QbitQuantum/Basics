INT_PTR CALLBACK
CFileDefExt::GeneralPageProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            LPPROPSHEETPAGEW ppsp = (LPPROPSHEETPAGEW)lParam;

            if (ppsp == NULL || !ppsp->lParam)
                break;

            TRACE("WM_INITDIALOG hwnd %p lParam %p ppsplParam %S\n", hwndDlg, lParam, ppsp->lParam);

            CFileDefExt *pFileDefExt = (CFileDefExt*)ppsp->lParam;
            SetWindowLongPtr(hwndDlg, DWLP_USER, (LONG_PTR)pFileDefExt);
            pFileDefExt->InitGeneralPage(hwndDlg);
            break;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == 14024) /* Opens With - Change */
            {
                CFileDefExt *pFileDefExt = (CFileDefExt*)GetWindowLongPtr(hwndDlg, DWLP_USER);
                OPENASINFO oainfo;
                oainfo.pcszFile = pFileDefExt->m_wszPath;
                oainfo.pcszClass = NULL;
                oainfo.oaifInFlags = OAIF_REGISTER_EXT|OAIF_FORCE_REGISTRATION;
                return SUCCEEDED(SHOpenWithDialog(hwndDlg, &oainfo));
            }
            else if (LOWORD(wParam) == 14021 || LOWORD(wParam) == 14022 || LOWORD(wParam) == 14023) /* checkboxes */
                PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
           else if (LOWORD(wParam) == 14001) /* Name */
            {
                if (HIWORD(wParam) == EN_CHANGE)
                    PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
            }
            break;
        case WM_NOTIFY:
        {
            LPPSHNOTIFY lppsn = (LPPSHNOTIFY)lParam;
            if (lppsn->hdr.code == PSN_APPLY)
            {
                CFileDefExt *pFileDefExt = (CFileDefExt*)GetWindowLongPtr(hwndDlg, DWLP_USER);

                /* Update attributes first */
                DWORD dwAttr = GetFileAttributesW(pFileDefExt->m_wszPath);
                if (dwAttr)
                {
                    dwAttr &= ~(FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_ARCHIVE);

                    if (BST_CHECKED == SendDlgItemMessageW(hwndDlg, 14021, BM_GETCHECK, 0, 0))
                        dwAttr |= FILE_ATTRIBUTE_READONLY;
                    if (BST_CHECKED == SendDlgItemMessageW(hwndDlg, 14022, BM_GETCHECK, 0, 0))
                        dwAttr |= FILE_ATTRIBUTE_HIDDEN;
                    if (BST_CHECKED == SendDlgItemMessageW(hwndDlg, 14023, BM_GETCHECK, 0, 0))
                        dwAttr |= FILE_ATTRIBUTE_ARCHIVE;

                    if (!SetFileAttributesW(pFileDefExt->m_wszPath, dwAttr))
                        ERR("SetFileAttributesW failed\n");
                }

                /* Update filename now */
                WCHAR wszBuf[MAX_PATH];
                StringCchCopyW(wszBuf, _countof(wszBuf), pFileDefExt->m_wszPath);
                LPWSTR pwszFilename = PathFindFileNameW(wszBuf);
                UINT cchFilenameMax = _countof(wszBuf) - (pwszFilename - wszBuf);
                if (GetDlgItemTextW(hwndDlg, 14001, pwszFilename, cchFilenameMax))
                {
                    if (!MoveFileW(pFileDefExt->m_wszPath, wszBuf))
                        ERR("MoveFileW failed\n");
                }
                    
                SetWindowLongPtr(hwndDlg, DWL_MSGRESULT, PSNRET_NOERROR);
                return TRUE;
            }
            break;
        }
        default:
            break;
    }

    return FALSE;
}