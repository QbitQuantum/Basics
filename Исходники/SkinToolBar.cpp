void CSkinToolBar::DrawItem(CDC*pDC, int nIndex)
{
    CSkinToolBarItem * lpItem = GetItemByIndex(nIndex);
    if (NULL == lpItem)
        return;

    CRect rcItem;
    GetItemRectByIndex(nIndex, rcItem);

    CRect rcLeft, rcRight;
    if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN
            || lpItem->m_dwStyle & STBI_STYLE_WHOLEDROPDOWN)
    {
        rcLeft = rcItem;
        rcLeft.right = rcLeft.left + lpItem->m_nLeftWidth;

        rcRight = rcItem;
        rcRight.left += lpItem->m_nLeftWidth;
        rcRight.right = rcRight.left + lpItem->m_nRightWidth;
    }

    if (lpItem->m_dwStyle & STBI_STYLE_SEPARTOR)
    {
        if (lpItem->m_lpSepartorImg != NULL && !lpItem->m_lpSepartorImg->IsNull())
            lpItem->m_lpSepartorImg->Draw(pDC, rcItem);
        return;
    }

    if ((lpItem->m_dwStyle & STBI_STYLE_CHECK) && lpItem->m_bChecked)
    {
        if (lpItem->m_lpBgImgD != NULL && !lpItem->m_lpBgImgD->IsNull())
            lpItem->m_lpBgImgD->Draw(pDC, rcItem);

        rcItem.OffsetRect(1, 1);

        if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN)
        {
            if (lpItem->m_lpLeftD != NULL && !lpItem->m_lpLeftD->IsNull())
                lpItem->m_lpLeftD->Draw(pDC, rcLeft);
            rcLeft.OffsetRect(1, 1);
        }

        if (m_nPressIndex == nIndex)
        {
            if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN)
            {
                if (!m_bPressLorR)
                {
                    if (lpItem->m_lpRightD != NULL && !lpItem->m_lpRightD->IsNull())
                        lpItem->m_lpRightD->Draw(pDC, rcRight);

                    rcRight.OffsetRect(1, 1);
                }
            }
        }
        else if (m_nHoverIndex == nIndex)
        {
            if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN)
            {
                if (!m_bHoverLorR)
                {
                    if (lpItem->m_lpRightH != NULL && !lpItem->m_lpRightH->IsNull())
                        lpItem->m_lpRightH->Draw(pDC, rcRight);
                }
            }
        }
    }
    else
    {
        if (m_nPressIndex == nIndex)
        {
            if (lpItem->m_lpBgImgD != NULL && !lpItem->m_lpBgImgD->IsNull())
                lpItem->m_lpBgImgD->Draw(pDC, rcItem);

            if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN)
            {
                if (m_bPressLorR)
                {
                    if (lpItem->m_lpLeftD != NULL && !lpItem->m_lpLeftD->IsNull())
                        lpItem->m_lpLeftD->Draw(pDC, rcLeft);
                }
                else
                {
                    if (lpItem->m_lpRightD != NULL && !lpItem->m_lpRightD->IsNull())
                        lpItem->m_lpRightD->Draw(pDC, rcRight);
                }
            }

            rcItem.OffsetRect(1, 1);

            if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN
                    || lpItem->m_dwStyle & STBI_STYLE_WHOLEDROPDOWN)
            {
                if (m_bPressLorR)
                    rcLeft.OffsetRect(1, 1);
                else
                    rcRight.OffsetRect(1, 1);
            }
        }
        else if (m_nHoverIndex == nIndex)
        {
            if (lpItem->m_lpBgImgH != NULL && !lpItem->m_lpBgImgH->IsNull())
                lpItem->m_lpBgImgH->Draw(pDC, rcItem);

            if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN)
            {
                if (m_bHoverLorR)
                {
                    if (lpItem->m_lpLeftH != NULL && !lpItem->m_lpLeftH->IsNull())
                        lpItem->m_lpLeftH->Draw(pDC, rcLeft);
                }
                else
                {
                    if (lpItem->m_lpRightH != NULL && !lpItem->m_lpRightH->IsNull())
                        lpItem->m_lpRightH->Draw(pDC, rcRight);
                }
            }
        }
    }

    BOOL bHasText = FALSE;
    if (lpItem->m_strText.GetLength() > 0)
        bHasText = TRUE;

    BOOL bHasIcon = FALSE;
    if (lpItem->m_lpIconImg != NULL && !lpItem->m_lpIconImg->IsNull())
        bHasIcon = TRUE;

    if (!(lpItem->m_dwStyle & STBI_STYLE_DROPDOWN
            || lpItem->m_dwStyle & STBI_STYLE_WHOLEDROPDOWN))
        rcLeft = rcItem;

    if (bHasIcon && bHasText)	// 带图标和文字
    {
        int cxIcon = lpItem->m_lpIconImg->GetWidth();
        int cyIcon = lpItem->m_lpIconImg->GetHeight();

        int nMode = pDC->SetBkMode(TRANSPARENT);
        HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
        if (NULL == hFont)
            hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
        HFONT hOldFont = (HFONT)pDC->SelectObject(hFont);

        CRect rcText(0,0,0,0);	// 计算文字宽高
        pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, DT_SINGLELINE | DT_CALCRECT);

        int cx = cxIcon+1+rcText.Width();
        int cy = cyIcon;

        CRect rcCenter;
        CalcCenterRect(rcLeft, cx, cy, rcCenter);

        CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
        lpItem->m_lpIconImg->Draw(pDC, rcIcon);

        UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
        rcText = CRect(rcIcon.right+1, rcLeft.top, rcIcon.right+1+rcText.Width(), rcLeft.bottom);
        pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, nFormat);

        pDC->SelectObject(hOldFont);
        pDC->SetBkMode(nMode);
    }
    else if (bHasIcon)	// 仅图标
    {
        int cxIcon = lpItem->m_lpIconImg->GetWidth();
        int cyIcon = lpItem->m_lpIconImg->GetHeight();

        CRect rcIcon;
        CalcCenterRect(rcLeft, cxIcon, cyIcon, rcIcon);

        lpItem->m_lpIconImg->Draw(pDC, rcIcon);
    }
    else if (bHasText)	// 仅文字
    {
        UINT nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

        int nMode = pDC->SetBkMode( TRANSPARENT);
        HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
        if (NULL == hFont)
            hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
        HFONT hOldFont = (HFONT)pDC->SelectObject(hFont);
        pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcLeft, nFormat);
        pDC->SelectObject(hOldFont);
        pDC->SetBkMode(nMode);
    }

    if (lpItem->m_dwStyle & STBI_STYLE_DROPDOWN
            || lpItem->m_dwStyle & STBI_STYLE_WHOLEDROPDOWN)
    {
        if (lpItem->m_lpArrowImg != NULL && !lpItem->m_lpArrowImg->IsNull())
        {
            int cxArrow = lpItem->m_lpArrowImg->GetWidth();
            int cyArrow = lpItem->m_lpArrowImg->GetHeight();

            CRect rcArrow;
            CalcCenterRect(rcRight, cxArrow, cyArrow, rcArrow);
            rcArrow.left = rcRight.left;
            rcArrow.right = rcArrow.left + cxArrow;

            lpItem->m_lpArrowImg->Draw(pDC, rcArrow);
        }
    }
}