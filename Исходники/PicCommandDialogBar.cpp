void PicCommandListBox::DrawItem(DRAWITEMSTRUCT *pDrawItemStruct)
{
    PicCommandDialogBar *pParent = static_cast<PicCommandDialogBar*>(GetParent());
    CPicDoc* pDoc = pParent->GetDocument();
    ASSERT_VALID(pDoc);
    if (pDoc)
    {
        const PicResource *ppic = pDoc->GetPicResource();
        if (ppic)
        {
            ASSERT(pDrawItemStruct->CtlType == ODT_LISTBOX);
            CDC dc;
            dc.Attach(pDrawItemStruct->hDC);

            // REVIEW: We need to use this font when measuring too.
            HGDIOBJ hFontOld = dc.SelectObject(&g_PaintManager->m_FontNormalBC);

            // Save these values to restore them when done drawing.
            COLORREF crOldTextColor = dc.GetTextColor();
            COLORREF crOldBkColor = dc.GetBkColor();
            int iMode = dc.GetBkMode();

            // If this item is selected, set the background color 
            // and the text color to appropriate values. Also, erase
            // rect by filling it with the background color.
            BOOL bSelected = (pDrawItemStruct->itemAction | ODA_SELECT) && (pDrawItemStruct->itemState & ODS_SELECTED);
            if (bSelected)
            {
                dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
                dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
                dc.FillSolidRect(&pDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
            }
            else
            {
                dc.FillSolidRect(&pDrawItemStruct->rcItem, crOldBkColor);
            }

            // If this item has the focus, draw a greenbackground around the
            // item's rect - unless it was selected.
            if (!bSelected && (pDrawItemStruct->itemAction | ODA_FOCUS) &&
                (pDrawItemStruct->itemState & ODS_FOCUS))
            {
                CBrush br(RGB(200, 255, 200));
                dc.FrameRect(&pDrawItemStruct->rcItem, &br);
            }

            // If this is the current pos, draw a caret.
            if (pDrawItemStruct->itemID == pParent->GetCurrentPosition())
            {
                // Draw the top of a "caret"
                int y = pDrawItemStruct->rcItem.bottom - 1;
                CPen br1(PS_SOLID, 1, RGB(0, 128, 0));
                HGDIOBJ hGdiObj = dc.SelectObject(&br1);
                dc.MoveTo(CPoint(pDrawItemStruct->rcItem.left, y));
                dc.LineTo(CPoint(pDrawItemStruct->rcItem.right - 1, y));

                y--;
                CPen br2(PS_SOLID, 1, RGB(0, 230, 0));
                dc.SelectObject(&br2);
                dc.MoveTo(CPoint(pDrawItemStruct->rcItem.left, y));
                dc.LineTo(CPoint(pDrawItemStruct->rcItem.right - 1, y));

                dc.SelectObject(hGdiObj);
            }
            else if (pDrawItemStruct->itemID == (pParent->GetCurrentPosition() + 1))
            {
                // FEATURE: Draw the bottom of a "caret"
            }


            if (pDrawItemStruct->itemID != -1)
            {
                TCHAR szName[256];
                if (pDrawItemStruct->itemID == 0)
                {
                    StringCchCopy(szName, ARRAYSIZE(szName), TEXT("Start"));
                }
                else
                {
                    // -1, since we have an additional entry at the top.
                    const PicCommand &command = ppic->GetCommandAt(pDrawItemStruct->itemID - 1);
                    ASSERT(command.type != PicCommand::None);
                    command.GetName(szName, ARRAYSIZE(szName));

                    if (!bSelected)
                    {
                        // For items that aren't selected, color them accordingly.
                        dc.SetTextColor(Command_GetColor(&command));
                    }
                }

                dc.SetBkMode(TRANSPARENT);

                // Draw the text.
                dc.DrawText(
                    szName,
                    -1,
                    &pDrawItemStruct->rcItem,
                    DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            }

            // Reset the background color and the text color back to their
            // original values.
            dc.SelectObject(hFontOld);
            dc.SetTextColor(crOldTextColor);
            dc.SetBkColor(crOldBkColor);
            dc.SetBkMode(iMode);
            dc.Detach();
        }
    }
}