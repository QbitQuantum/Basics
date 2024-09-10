int CDocStructRecordItem::Draw(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (pDrawArgs->pDC == NULL || pDrawArgs->pControl == NULL || pDrawArgs->pRow == NULL || pDrawArgs->pItem == NULL) {
        ASSERT(FALSE);
        return 0;
    }
    int offSet = 0;
    CDC* pDC = pDrawArgs->pDC;
    int nTreeDepth = pDrawArgs->pRow->GetTreeDepth();
    int nLeftIndent = pDrawArgs->pControl->GetIndent(nTreeDepth);
    CRect rcRow = pDrawArgs->pRow->GetRect();
    nTreeDepth == 0 ? offSet = 0 : offSet = 0;
    CXTPOffice2007Image *pImage = XTPOffice2007Images()->LoadFile(_T("PUSHBUTTON"));
    ASSERT(pImage);
    int nState = 0;

    if (pDrawArgs->pRow->IsSelected() == TRUE) {
        nState = 2;
    }
    CDocStructRecord* pRecord = (CDocStructRecord*)GetRecord();
    if (pRecord) {
        int nCurrentLayout = pRecord->m_nCurrentLayout;

        if (nCurrentLayout == DocumentStructureLayout(Thumbnail)) {
            rcRow.left += nTreeDepth * TREE_DEPTH_OFFSET;
            rcRow.top += 2;
            rcRow.bottom -= 2;
            rcRow.right -= nTreeDepth * TREE_DEPTH_OFFSET;
        } else {
            rcRow.left += 0; //nLeftIndent + offSet;
        }
        if (pImage) {
            // Draw a blue rectangle that surrounds all child items to show that an item is part of a group.
            if (nCurrentLayout == DocumentStructureLayout(Thumbnail) && pDrawArgs->pRow->GetParentRow() != NULL) {
                int nTopRow = pDrawArgs->pControl->GetTopRowIndex();
                int nVisibleRows = GetReportAreaRows(pDrawArgs->pControl, pDrawArgs->pControl->GetTopRowIndex(), TRUE);
                CXTPReportRow *pTopRow = pDrawArgs->pControl->GetRows()->GetAt(nTopRow);

                if (pTopRow != NULL) {
                    if (pTopRow->GetTreeDepth() > 1 && pTopRow == pDrawArgs->pRow) {
                        for (int i = 1; i < pTopRow->GetTreeDepth(); i++) {
                            int iExpandedChildsHeight = GetExpandedChildsHeight(pDrawArgs->pControl, pDrawArgs->pRow->GetParentRow()->GetRecord());
                            CRect rcParentRect(pTopRow->GetRect());
                            bool bReset = false;
                            for (int j = nTopRow; j < nTopRow + nVisibleRows ; j++) {
                                int iRowLevel = pDrawArgs->pControl->GetRows()->GetAt(j)->GetTreeDepth();
                                if (iRowLevel >= i+1) {
                                    if (bReset == false) {
                                        iExpandedChildsHeight = 0;
                                        bReset = true;
                                    }
                                    iExpandedChildsHeight += pDrawArgs->pControl->GetPaintManager()->GetRowHeight(NULL, pDrawArgs->pControl->GetRows()->GetAt(j));
                                } else {
                                    break;
                                }
                            }
                            rcParentRect.bottom = iExpandedChildsHeight < pDrawArgs->pControl->GetReportRectangle().bottom ? iExpandedChildsHeight : pDrawArgs->pControl->GetReportRectangle().bottom + 2;
                            rcParentRect.left += i * TREE_DEPTH_OFFSET;
                            rcParentRect.right -= i * TREE_DEPTH_OFFSET;
                            pImage->DrawImage(pDC, rcParentRect, pImage->GetSource(0, 5), CRect(4, 4, 4, 4), COLORREF_NULL);
                        }
                    }
                }
            }
            // Draw an orange/blue image over item.
            if ((nCurrentLayout == DocumentStructureLayout(Thumbnail)) ||((nCurrentLayout == DocumentStructureLayout(Compact)) && nState == 2)) {
                if (pRecord->IsPage()) {
                    pImage->DrawImage(pDC, rcRow, pImage->GetSource(nState, 5), CRect(4, 4, 4, 4), COLORREF_NULL);
                } else {
                    // take tree depth and draw button images of tree depth size.
                    CRect newRowOffset(rcRow);
                    if (pDrawArgs->pRow->GetTreeDepth() != 0 && nCurrentLayout == DocumentStructureLayout(Thumbnail)) {
                        newRowOffset.bottom += GetExpandedChildsHeight(pDrawArgs->pControl, pDrawArgs->pRow->GetRecord());
                        if ( pDrawArgs->pRow->IsExpanded() == TRUE ) {
                            newRowOffset.bottom += 1;
                        }
                        pImage->DrawImage(pDC, newRowOffset, pImage->GetSource(0, 5), CRect(4, 4, 4, 4), COLORREF_NULL);
                    }

                    if (pDrawArgs->pRow->GetTreeDepth() == 0) {
                        pImage->DrawImage(pDC, rcRow, pImage->GetSource(nState, 5), CRect(4, 4, 4, 4), COLORREF_NULL);
                    }

                    if (nState == 2) {
                        pImage->DrawImage(pDC, rcRow, pImage->GetSource(nState, 5), CRect(4, 4, 4, 4), COLORREF_NULL);
                    }
                }
            }
        }
        pDC->SetBkMode(TRANSPARENT);
        if (nCurrentLayout == DocumentStructureLayout(Thumbnail) && pRecord->IsPage()) {
            int x = rcRow.left + RECORD_ITEM_OFFSET;
            int y = rcRow.top + RECORD_ITEM_OFFSET;

            int nWidth = rcRow.Width() - 2*RECORD_ITEM_OFFSET;
            int nHeight = nWidth * 3/4;

            if (nWidth > rcRow.Width()) {
                nWidth = rcRow.Width();
            }
            CRect rcThumb;
            rcThumb.SetRect(x, y, x + nWidth, y + nHeight);
            if (pRecord->m_pContainer != NULL) {
                pRecord->m_pContainer->DrawThumbWhiteboard(pRecord->m_pvData, rcThumb, pDC);
            }
        }
    }

    // Code taken from CXTPReportControlItem::Draw - but a bit modified
    m_pControl = pDrawArgs->pControl;

    CRect& rcItem = pDrawArgs->rcItem;
    CXTPReportPaintManager* pPaintManager = pDrawArgs->pControl->GetPaintManager();

    CRgn rgn;
    rgn.CreateRectRgn(rcItem.left, rcItem.top - 1, rcItem.right, rcItem.bottom);

    if (!pDC->IsPrinting()) {
        pDC->SelectClipRgn(&rgn);
    }

    XTP_REPORTRECORDITEM_METRICS* pMetrics = new XTP_REPORTRECORDITEM_METRICS();
    pMetrics->strText = GetCaption(pDrawArgs->pColumn);
    pDrawArgs->pRow->GetItemMetrics(pDrawArgs, pMetrics);

    ASSERT(pMetrics->pFont);
    ASSERT(pMetrics->clrForeground != XTP_REPORT_COLOR_DEFAULT);

    int nItemGlyphs = rcItem.left;

    // draw tree inside item rect (see also HitTest function)
    if (pDrawArgs->pColumn && pDrawArgs->pColumn->IsTreeColumn()) {
        int nTreeDepth = pDrawArgs->pRow->GetTreeDepth() - pDrawArgs->pRow->GetGroupLevel();
        if (nTreeDepth > 0) {
            nTreeDepth++;
        }
        rcItem.left += pDrawArgs->pControl->GetIndent(nTreeDepth);

        BOOL bHasChildren = pDrawArgs->pControl->IsVirtualMode() ?
            pDrawArgs->pRow->GetTreeDepth() == 0 && (pMetrics->nVirtRowFlags & xtpVirtRowHasChildren) :
        pDrawArgs->pRow->HasChildren();

        CRect rcBitmap(rcItem);
        CSize sizeBitmap = pPaintManager->DrawCollapsedBitmap(NULL, pDrawArgs->pRow, rcBitmap);

        int nIconAlign = pDrawArgs->nTextAlign & xtpColumnIconMask;

        // horizontal alignment
        switch (nIconAlign) {
        case xtpColumnIconRight:
            rcBitmap.left = rcBitmap.right - sizeBitmap.cx - 2;
            break;
        case xtpColumnIconLeft:
            rcBitmap.right = rcBitmap.left + sizeBitmap.cx + 2;
            break;
        }
        // vertical alignment
        switch (nIconAlign) {
        case xtpColumnIconTop:
            rcBitmap.bottom = rcBitmap.top + sizeBitmap.cy + 2;
            break;
        case xtpColumnIconBottom:
            rcBitmap.top = rcBitmap.bottom - sizeBitmap.cy - 2;
            break;
        }
        bool bDrawArrow = false;
        if (bHasChildren || (pRecord->IsDocument() && !pRecord->IsEmptyDocument())) {
            bDrawArrow = true;
        }

        if (pRecord->IsDocument() && !pRecord->IsLoadedDocument()) {
            pDrawArgs->pRow->SetExpanded(FALSE);
        }
        sizeBitmap = pPaintManager->DrawCollapsedBitmap(bDrawArrow ? pDC : NULL, pDrawArgs->pRow, rcBitmap);

        if (!pDC->IsPrinting() && bHasChildren) {
            pDrawArgs->pRow->SetCollapseRect(rcBitmap);
        }

        // Draw a custom image at the left side of the record item
        if (pPaintManager->GetRuntimeClass() == RUNTIME_CLASS(CXTPDocumentStructurePaintManager)) {
            if (pRecord->IsChapter() || pRecord->IsDocument()) {
                CRect rcBitmap(rcItem);
                if (((CDocStructRecord*) pDrawArgs->pRow->GetRecord())->m_nCurrentLayout == DocumentStructureLayout(Thumbnail)) {
                    rcBitmap.left += 15;
                    rcBitmap.top -= 5;
                    CSize csBitmap = ((CXTPDocumentStructurePaintManager*)pPaintManager)->DrawCustomBitmap(pDC, pDrawArgs->pRow, rcBitmap, m_nImageIndex);
                    rcItem.left += sizeBitmap.cx + 35;
                } else {
                    rcBitmap.left += 18;
                    CSize csBitmap = ((CXTPDocumentStructurePaintManager*)pPaintManager)->DrawCustomBitmap(pDC, pDrawArgs->pRow, rcBitmap, m_nImageIndex);
                    rcItem.left += sizeBitmap.cx + 25;
                }
            } else {
                if (((CDocStructRecord*) pDrawArgs->pRow->GetRecord())->m_nCurrentLayout == DocumentStructureLayout(Compact)) {
                    rcBitmap.left += 15;
                    CSize csBitmap = ((CXTPDocumentStructurePaintManager*)pPaintManager)->DrawCustomBitmap(pDC, pDrawArgs->pRow, rcBitmap, m_nImageIndex);
                    rcItem.left += sizeBitmap.cx + 10;
                }
                rcItem.left += sizeBitmap.cx + 2;
            }
        }
    }

    COLORREF clrText = XTPOffice2007Images()->GetImageColor(_T("LISTBOX"), _T("NormalText"));
    pDC->SetTextColor(clrText);

    CFont* pOldFont = (CFont*)pDC->SelectObject(pMetrics->pFont);

    if (pMetrics->clrBackground != XTP_REPORT_COLOR_DEFAULT) {
        pDC->SetBkColor(pMetrics->clrBackground);
    } else {
        pDC->SetBkColor(pPaintManager->m_clrControlBack);
    }

    if (m_bHasCheckbox) {
        DrawCheckBox(pDrawArgs, rcItem);
    }

    // Do the draw bitmap pDC, rcItem, GetIconIndex()
    if (pMetrics->nItemIcon != XTP_REPORT_NOICON || GetIconIndex() != XTP_REPORT_NOICON) {
        pPaintManager->DrawItemBitmap(pDrawArgs, rcItem, pMetrics->nItemIcon != XTP_REPORT_NOICON ? pMetrics->nItemIcon : GetIconIndex());
    }
    nItemGlyphs = (rcItem.left - nItemGlyphs);

    OnDrawControls(pDrawArgs, rcItem);
    if (rcItem.Width()) {
        OnDrawCaption(pDrawArgs, pMetrics);
    }

    int nItemTextWidth = nItemGlyphs + 7;
    if (m_pMarkupUIElement) {
        nItemTextWidth += XTPMarkupMeasureElement(m_pMarkupUIElement, rcItem.Width(), INT_MAX).cx;
    } else {
        nItemTextWidth += pDC->GetTextExtent(pMetrics->strText).cx;
    }

    pDC->SelectObject(pOldFont);
    pMetrics->InternalRelease();
    if (!pDC->IsPrinting()) {
        pDC->SelectClipRgn(NULL);
    }

    return nItemTextWidth;
}