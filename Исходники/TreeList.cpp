void CTreeList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    PULONG  pMagic = (PULONG) lpDrawItemStruct->itemData;

    TCHAR  lpBuffer[256];
    LV_ITEM lvi;
    LV_COLUMN lvc, lvcprev ;

    memset(lpBuffer, 0, 256);
    lvi.mask = LVIF_TEXT | LVIF_PARAM ;
    lvi.iItem = lpDrawItemStruct->itemID ;  
    lvi.iSubItem = 0;
    lvi.pszText = lpBuffer ;
    lvi.cchTextMax = sizeof(lpBuffer);
    GetItem(&lvi);
    ::ZeroMemory(&lvc, sizeof(lvc));
    ::ZeroMemory(&lvcprev, sizeof(lvcprev));
    lvc.mask = LVCF_WIDTH |LVCF_FMT;
    lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

    CDC* pDC;
    pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    int nCol;
    CRect rcText = lpDrawItemStruct->rcItem;

    CFont Fnt, *pOldFont = NULL;
    LOGFONT lf;

    int cyPixels = pDC->GetDeviceCaps(LOGPIXELSY);
    memset(&lf, 0, sizeof(LOGFONT));

    if (pMagic == NULL) {
        return;
    }

    if (*pMagic == EXT2_CDROM_DEVICE_MAGIC || *pMagic == EXT2_DISK_MAGIC) {

        if (IsVistaOrAbove()) {
            lstrcpy(lf.lfFaceName, "MS Sans Serif"); /*Courier New*/
            lf.lfHeight = -MulDiv(8, cyPixels, 72);
            lf.lfWeight = TRUE;
        } else {
            lstrcpy(lf.lfFaceName, "Arial Black"); /*Courier New*/
            lf.lfHeight = -MulDiv(8, cyPixels, 72);
            lf.lfWeight = TRUE;
        }
    } else {
        lstrcpy(lf.lfFaceName, "MS Sans Serif");
        lf.lfHeight = -MulDiv(8, cyPixels, 72);
    }

    Fnt.CreateFontIndirect(&lf);
    pOldFont = (CFont *) pDC->SelectObject(&Fnt);

    /* loading bitmap */
    if (m_hBitmap == NULL) {
        m_hBitmap = (HBITMAP)::LoadImage(GetModuleHandle(NULL), 
                             MAKEINTRESOURCE(IDB_LINE_SEP),
                             IMAGE_BITMAP, 0, 0, 0);

        if (m_hBitmap) {
            m_hMemDC  = ::CreateCompatibleDC(this->GetDC()->m_hDC);
            m_hOldBmp = (HBITMAP)::SelectObject(m_hMemDC, m_hBitmap);
        }
    }

    if (TRUE) {

        if (!m_SelectionFlag) {
            for (nCol=0; GetColumn(nCol, &lvc); nCol++) {
                if (nCol > 0) {
                    GetSubItemRect(lpDrawItemStruct->itemID, 
                        nCol,LVIR_BOUNDS, m_SelectionRect);
                } else {
                    GetItemRect(lpDrawItemStruct->itemID, 
                             m_SelectionRect,LVIR_BOUNDS);
                    m_SelectionRect.right = GetColumnWidth(0);
                    m_SelectionRect.left = 0;
                }

                if (m_SelectionRect.PtInRect(m_Point)) {
                    m_SelectionFlag = TRUE;
                    break;
                } else {
                    m_SelectionFlag = FALSE;
                }
            } 
        }
 
        if ((lpDrawItemStruct->itemState & ODS_SELECTED) && m_SelectionFlag ) {

            CRect rc = lpDrawItemStruct->rcItem;
            rc.left  += 4; rc.right -= 4;
            rc.top   += 1; rc.bottom -= 0;
            if (*pMagic == EXT2_CDROM_DEVICE_MAGIC || *pMagic == EXT2_DISK_MAGIC) {
                rc.bottom -= 3; rc.top -= 1;
                rc.right = (rc.Width() * 7 / 8) + rc.left;
            }
            pDC->FillSolidRect(&rc, GetSysColor(m_bFocus ? COLOR_HIGHLIGHT : COLOR_INACTIVEBORDER));
        } else {
            CRect rc = lpDrawItemStruct->rcItem;
            pDC->FillSolidRect(&rc, GetSysColor(COLOR_WINDOW)) ;
            pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT)) ; 
        }
    }

    for (nCol=0; GetColumn(nCol, &lvc); nCol++) {

        UINT  uFormat    = DT_LEFT ;

        if (*pMagic == EXT2_CDROM_DEVICE_MAGIC || *pMagic == EXT2_DISK_MAGIC) {

            rcText = lpDrawItemStruct->rcItem;
            rcText.left += 4;
            rcText.bottom += 1;
            rcText.top = rcText.bottom - 6 + lf.lfHeight;

            ::DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), 
                              &rcText, DT_LEFT) ;

            CRect rect = lpDrawItemStruct->rcItem;
            int rc = 0;
            BITMAP  cs;


            rect.top = rcText.bottom - 4;
            rc = ::GetObject(m_hBitmap, sizeof(cs), &cs);
            if (rc == 0) {
                pDC->SelectObject(pOldFont);
                return;
            }

            ::StretchBlt(pDC->m_hDC, rect.left + 4, (rect.bottom + rect.top) / 2,
                         rect.Width() * 7 / 8, cs.bmHeight,
                         m_hMemDC, 0, 0, cs.bmWidth, cs.bmHeight, SRCCOPY);

        } else {

            if (nCol > 0) {
               GetColumn(nCol, &lvcprev) ;
               rcText.left = rcText.right;
               rcText.right += lvcprev.cx;
               rcText.left += 4;

                if (nCol == 3 || nCol == 4) {
                    uFormat = DT_RIGHT;
                    rcText.right -= 4;
                }

            } else {
                rcText = lpDrawItemStruct->rcItem;
                rcText.top += (16 + lf.lfHeight) / 2;
                rcText.right = rcText.left + GetColumnWidth(0);
                rcText.left += 20;
            }

            // Get and draw the text 
            memset(lpBuffer, 0, 256);
            ::ZeroMemory(&lvi, sizeof(lvi));
            lvi.iItem = lpDrawItemStruct->itemID;
            lvi.mask = LVIF_TEXT | LVIF_PARAM;
            lvi.iSubItem = nCol;
            lvi.pszText = lpBuffer;
            lvi.cchTextMax = sizeof(lpBuffer);
            GetItem(&lvi);
   
            ::DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), 
                              &rcText, uFormat) ;

            if (nCol == 0) {
                rcText.left -= 20;
            } else {
                rcText.left -= 4;
                if (nCol == 3 || nCol == 4) {
                    rcText.right += 4;
                }
            }
        }
    }

    pDC->SelectObject(pOldFont);

    return;
}