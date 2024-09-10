void DoGetRepStuff(HWND hwnd, LPINSERTITEM pfr)
{                 
    HD_ITEM hi;
    int ret;
    HD_ITEM FAR* pitem;
    HGLOBAL hglb;
    int iAlloc;
    
    
    hi.mask = pfr->mask;
    hi.cxy = pfr->cxy;
    if (pfr->Nullpitem)
        pitem = NULL;
    else
        pitem = &hi;
            
    hi.cchTextMax = pfr->cchTextMax;
//  hi.cchTextMax = MAX_PSZTEXT;
    hi.fmt = pfr->fmt;
    hi.lParam = pfr->lParam;
    
    
    if (hi.cchTextMax == 0)
        iAlloc = MAX_PSZTEXT;
    else 
        iAlloc = hi.cchTextMax;
            
    if (pfr->NullpszText) 
        hi.pszText = NULL;              // can this be done ??
    else {
        hglb = GlobalAlloc(GPTR, iAlloc);
        hi.pszText = (LPSTR) GlobalLock(hglb);
//      _fstrcpy(hi.pszText, pfr->pszText);
    } 
    
    if (pfr->NullHwd) 
        ret = Header_GetItem(NULL, pfr->index, pitem);
    else
        ret = Header_GetItem(pfr->hwnd, pfr->index, pitem);

    wsprintf(szDbgMsg, "%d = Header_GetItem(index = %d,  \n\
    mask = %x )", ret, pfr->index, hi.mask);
    MyDebugMsg(DM_TRACE, "%s", (LPCSTR) szDbgMsg);
    SetDlgItemInt(hwnd, IDC_INSERTRET, ret, TRUE) ;
    
    if (ret) {
        SetDlgItemInt(hwnd, IDC_INSERTCXY, hi.cxy, TRUE);  
        SetDlgItemInt(hwnd, IDC_INSERTCCHTEXTMAX, hi.cchTextMax, TRUE);
        wsprintf(szTemp, szLongFilter, hi.lParam);
        SetDlgItemText(hwnd, IDC_INSERTLPARAM, szTemp);
        SetDlgItemText(hwnd, IDC_INSERTTEXT, hi.pszText);
        wsprintf(szTemp, "%04hx", hi.mask);
        SetDlgItemText(hwnd, IDC_INSERTMASK, szTemp);
        CheckDlgButton(hwnd, IDC_INSERTHDRIGHT, hi.fmt & HDF_RIGHT);
        CheckDlgButton(hwnd, IDC_INSERTHDLEFT, hi.fmt & HDF_LEFT);
        CheckDlgButton(hwnd, IDC_INSERTHDCENTER, hi.fmt & HDF_CENTER);
        CheckDlgButton(hwnd, IDC_INSERTHDJUSTIFYMASK, hi.fmt & HDF_JUSTIFYMASK);
        CheckDlgButton(hwnd, IDC_INSERTHDOWNERDRAW, hi.fmt & HDF_OWNERDRAW);
        CheckDlgButton(hwnd, IDC_INSERTHDSTRING, hi.fmt & HDF_STRING);
        CheckDlgButton(hwnd, IDC_INSERTHDBITMAP, hi.fmt & HDF_BITMAP);
        wsprintf(szTemp, szLongFilter, (DWORD)  hi.hbm);
        SetDlgItemText(hwnd, IDC_INSERTHBM, szTemp);        
        wsprintf(szTemp, "%04x", hi.fmt);
//      SetDlgItemInt(hwnd, IDC_INSERTFMT, hi.fmt, TRUE); 
        SetDlgItemText(hwnd, IDC_INSERTFMT, szTemp);
    }
    
    if (!pfr->NullpszText) {
        GlobalUnlock(hglb);
        GlobalFree(hglb); 
    }
/****
  wsprintf(szTemp, szLongFilter, hwndFind) ;
  SetDlgItemText(hwnd, ID_INSERTRET, szTemp) ;
**/
}