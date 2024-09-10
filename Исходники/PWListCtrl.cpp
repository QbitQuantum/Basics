BOOL CPWListCtrl::OnEraseBkgnd(CDC* pDC)
{
  if (m_bFilterActive && app.GetMainDlg()->GetNumPassedFiltering() == 0) {
    int nSavedDC = pDC->SaveDC(); //save the current DC state

    // Set up variables
    COLORREF clrText = RGB(168, 0, 0);
    COLORREF clrBack = ::GetSysColor(COLOR_WINDOW);    //system background color
    CBrush cbBack(clrBack);

    CRect rc;
    GetClientRect(&rc);  //get client area of the ListCtrl

    // If there is a header, we need to account for the space it occupies
    CHeaderCtrl* pHC = GetHeaderCtrl();
    if (pHC != NULL) {
      CRect rcH;
      pHC->GetClientRect(&rcH);
      rc.top += rcH.bottom;
    }

    // Here is the string we want to display (or you can use a StringTable entry)
    const CString cs_emptytext(MAKEINTRESOURCE(IDS_NOITEMSPASSEDFILTERING));

    // Now we actually display the text
    // set the text color
    pDC->SetTextColor(clrText);
    // set the background color
    pDC->SetBkColor(clrBack);
    // fill the client area rect
    pDC->FillRect(&rc, &cbBack);
    // select a font
    pDC->SelectStockObject(ANSI_VAR_FONT);
    // and draw the text
    pDC->DrawText(cs_emptytext, -1, rc,
                  DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP);

    // Restore dc
    pDC->RestoreDC(nSavedDC);
    ReleaseDC(pDC);
  } else {
    //  If there are items in the ListCtrl, we need to call the base class function
    CListCtrl::OnEraseBkgnd(pDC);
  }

  return TRUE;
}