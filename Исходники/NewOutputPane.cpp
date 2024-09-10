void NewOutputPane::DrawItem(DRAWITEMSTRUCT *pDrawItemStruct)
{
    assert(pDrawItemStruct->CtlType == ODT_LISTBOX);
    assert(pDrawItemStruct->CtlID == IDC_LIST1);

    CDC *pDC = CDC::FromHandle(pDrawItemStruct->hDC);

    //HGDIOBJ hFontOld = pDC->SelectObject(&g_PaintManager->m_FontNormalBC);
    HGDIOBJ hFontOld = pDC->SelectObject(&g_PaintManager->m_FontNormal);
    COLORREF crOldTextColor = pDC->GetTextColor();
    int iMode = pDC->GetBkMode();
    COLORREF crOldBkColor = pDC->GetBkColor();
    pDC->FillSolidRect(&pDrawItemStruct->rcItem, crOldBkColor);

    std::vector<CompileResult> &results = _results[_GetCurrentType()];

    if ((pDrawItemStruct->itemID != -1) && (pDrawItemStruct->itemID < (int)results.size()))
    {
        CompileResult &result = results[pDrawItemStruct->itemID];

        if (pDrawItemStruct->itemState & ODS_SELECTED)
        {
            pDC->SetTextColor(g_PaintManager->GetColor(COLOR_HIGHLIGHTTEXT));
            pDC->SetBkColor(g_PaintManager->GetColor(COLOR_HIGHLIGHT));
            pDC->SetBkMode(OPAQUE);
        }
        else
        {
            pDC->SetTextColor(RGB(0, 0, 0));
            pDC->SetBkMode(TRANSPARENT);
        }

        // Draw the text.
        pDC->DrawText(
            result.GetMessageA().c_str(),
            -1,
            &pDrawItemStruct->rcItem,
            DT_SINGLELINE | DT_LEFT | DT_NOPREFIX);
    }

    pDC->SelectObject(hFontOld);
    pDC->SetTextColor(crOldTextColor);
    pDC->SetBkColor(crOldBkColor);
    pDC->SetBkMode(iMode);
}