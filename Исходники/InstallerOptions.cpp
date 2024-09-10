LRESULT WINAPI WMCommandProc(HWND hWnd, UINT id, HWND hwndCtl, UINT codeNotify) {
  int nIdx = FindControlIdx(id);
  // Ignore if the dialog is in the process of being created
  if (g_done || nIdx < 0)
    return 0;

  switch (pFields[nIdx].nType)
  {
    case FIELD_BROWSEBUTTON:
      --nIdx;
    case FIELD_LINK:
    case FIELD_BUTTON:
    case FIELD_CHECKBOX:
    case FIELD_RADIOBUTTON:
      if (codeNotify != BN_CLICKED)
        return 0;
      break;
    case FIELD_COMBOBOX:
    case FIELD_LISTBOX:
      if (codeNotify != LBN_SELCHANGE) // LBN_SELCHANGE == CBN_SELCHANGE
        return 0;
      break;
    default:
      return 0;
  }

  FieldType *pField = pFields + nIdx;

  char szBrowsePath[MAX_PATH];

  switch (pField->nType) {
    case FIELD_FILEREQUEST: {
      OPENFILENAME ofn={0,};

      ofn.lStructSize = sizeof(ofn);
      ofn.hwndOwner = hConfigWindow;
      ofn.lpstrFilter = pField->pszFilter;
      ofn.lpstrFile = szBrowsePath;
      ofn.nMaxFile  = sizeof(szBrowsePath);
      ofn.Flags = pField->nFlags & (OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_EXPLORER);

      GetWindowText(pField->hwnd, szBrowsePath, sizeof(szBrowsePath));

    tryagain:
      GetCurrentDirectory(BUFFER_SIZE, szResult); // save working dir
      if ((pField->nFlags & FLAG_SAVEAS) ? GetSaveFileName(&ofn) : GetOpenFileName(&ofn)) {
        mySetWindowText(pField->hwnd, szBrowsePath);
        SetCurrentDirectory(szResult); // restore working dir
                                       // OFN_NOCHANGEDIR doesn't always work (see MSDN)
        break;
      }
      else if (szBrowsePath[0] && CommDlgExtendedError() == FNERR_INVALIDFILENAME) {
        szBrowsePath[0] = '\0';
        goto tryagain;
      }

      break;
    }

    case FIELD_DIRREQUEST: {
      BROWSEINFO bi;

      bi.hwndOwner = hConfigWindow;
      bi.pidlRoot = NULL;
      bi.pszDisplayName = szBrowsePath;
      bi.lpszTitle = pField->pszText;
#ifndef BIF_NEWDIALOGSTYLE
#define BIF_NEWDIALOGSTYLE 0x0040
#endif
      bi.ulFlags = BIF_STATUSTEXT | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
      bi.lpfn = BrowseCallbackProc;
      bi.lParam = nIdx;
      bi.iImage = 0;

      if (pField->pszRoot) {
        LPSHELLFOLDER sf;
        ULONG eaten;
        LPITEMIDLIST root;
        int ccRoot = (lstrlen(pField->pszRoot) * 2) + 2;
        LPWSTR pwszRoot = (LPWSTR) MALLOC(ccRoot);
        MultiByteToWideChar(CP_ACP, 0, pField->pszRoot, -1, pwszRoot, ccRoot);
        SHGetDesktopFolder(&sf);
        sf->ParseDisplayName(hConfigWindow, NULL, pwszRoot, &eaten, &root, NULL);
        bi.pidlRoot = root;
        sf->Release();
        FREE(pwszRoot);
      }
      //CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
      LPITEMIDLIST pResult = SHBrowseForFolder(&bi);
      if (!pResult)
        break;

      if (SHGetPathFromIDList(pResult, szBrowsePath)) {
        mySetWindowText(pField->hwnd, szBrowsePath);
      }

      CoTaskMemFree(pResult);

      break;
    }

    case FIELD_LINK:
    case FIELD_BUTTON:
      // Allow the state to be empty - this might be useful in conjunction
      // with the NOTIFY flag
      if (*pField->pszState)
        ShellExecute(hMainWindow, NULL, pField->pszState, NULL, NULL, SW_SHOWDEFAULT);
      break;
  }

  if (pField->nFlags & LBS_NOTIFY) {
    // Remember which control was activated then pretend the user clicked Next
    g_NotifyField = nIdx + 1;
    mySendMessage(hMainWindow, WM_NOTIFY_OUTER_NEXT, 1, 0);
  }

  return 0;
}