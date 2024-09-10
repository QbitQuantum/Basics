void CBigFileListCtrl::DoDrawItem(CDCHandle dc, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CRect rcItem = lpDrawItemStruct->rcItem;
    size_t idx = (size_t)lpDrawItemStruct->itemData;
    int nItem = lpDrawItemStruct->itemID;
    BOOL bSelect = lpDrawItemStruct->itemState & ODS_SELECTED;
    CRect rcDraw;
    CVirtualDirManager* pDir = (CVirtualDirManager*)m_pOwner;
    CString strFilePath, strFile, strDir;
    HICON hIcon = NULL, hIconCache = NULL;
    int nCurrentEnd = rcItem.left;
    double percent;
    CRect rcClient;
    CFontHandle underlineFont = KuiFontPool::GetFont(FALSE, TRUE, FALSE);
    CFontHandle normalFont = KuiFontPool::GetFont(FALSE, FALSE, FALSE);

    // 绘制背景
    {
        rcDraw = rcItem;
        GetClientRect(rcClient);
        if (rcClient.right > rcDraw.right)
            rcDraw.right = rcClient.right;
        dc.FillSolidRect(rcDraw, RGB(0xff,0xff,0xff));
    }

    if (idx == -1)
    {
        CString strMore;
        dc.SelectFont(underlineFont);
        dc.SetTextColor(RGB(0x4d, 0x70, 0x96));
        strMore.Format(
            //_T("已经显示了%d个文件，还有%d个没有显示，点击此处查看全部"), 
            _T("还有%d个没有显示，点击此处查看全部"),
            //GetItemCount() - 1, 
            m_dwMoreItems);
        rcDraw = rcItem;
        dc.FillSolidRect(rcDraw, RGB(0xff, 0xff, 0xff));
        int nLeft = rcItem.left + GetColumnWidth(0) + GetColumnWidth(1);
        int nRight = nLeft + GetColumnWidth(2);
        rcDraw.left = nLeft;
        rcDraw.right = nRight;
        dc.DrawText(strMore, strMore.GetLength(), rcDraw, DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_CALCRECT);
        if (rcDraw.right > nRight)
            rcDraw.right = nRight;
        dc.DrawText(strMore, strMore.GetLength(), rcDraw, DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_END_ELLIPSIS);
        m_rcMore.left = rcDraw.left;
        m_rcMore.right = rcDraw.right;
        m_rcMore.top = 0;
        m_rcMore.bottom = m_nItemHeight;
        return;
    }

    if (idx == -2)
    {
        CString strNone;
        dc.SelectFont(normalFont);
        dc.SetTextColor(RGB(0, 0, 0));
        strNone = _T("没有发现文件，您可以重新扫描。");
        rcDraw = rcItem;
        dc.FillSolidRect(rcDraw, RGB(0xff, 0xff, 0xff));
        rcDraw.left = rcItem.left + GetColumnWidth(0) + GetColumnWidth(1);
        rcDraw.right = rcDraw.left + GetColumnWidth(2);
        dc.DrawText(strNone, strNone.GetLength(), rcDraw, DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_END_ELLIPSIS);
        return;
    }

    percent = (double)pDir->m_vCacheFiles[idx].qwFileSize / pDir->m_vCacheFiles[0].qwFileSize;
    rcDraw = rcItem;
    dc.SetTextColor(RGB(0,0,0));
    if (bSelect)
    {
        CPen penBorder;
        CBrush brushBk;
        CRect rcSelect = rcDraw;

        penBorder.CreatePen(PS_SOLID, 1, RGB(0x7d, 0xa2, 0xce));
        brushBk.CreateSolidBrush(RGB(0xeb, 0xf4, 0xfd));
        dc.SelectPen(penBorder);
        dc.SelectBrush(brushBk);
        dc.RoundRect(rcSelect, CPoint(3, 3));
        rcSelect.left += 2;
        rcSelect.right -= 2;
        rcSelect.top += 2;
        rcSelect.bottom -= 2;
        DrawGradualColorRect(dc, rcSelect, RGB(0xdd, 0xec, 0xfd), RGB(0xc2, 0xdc, 0xfd));
    }
    else
    {
        dc.FillSolidRect(rcDraw, RGB(0xff, 0xff, 0xff));
    }
    {
        // 画背景进度条
        CRect rcProgress = rcDraw;
        rcProgress.left += 2;
        rcProgress.right -= 2;
        rcProgress.top += 2;
        rcProgress.bottom -= 2;
        rcProgress.right = rcProgress.left + int(rcProgress.Width() * percent);
        COLORREF color1 = RGB(0xff, 0xf4, 0xcc);
        COLORREF color2 = RGB(0xff, 0xde, 0x5c);
        COLORREF color3 = RGB(0xff, 0xf4 + (0xde - 0xf4) * percent, 0xcc + (0x5c - 0xcc) * percent);
        DrawGradualColorRect(dc, rcProgress, color1, color3, FALSE);
    }
    //rcDraw.top = rcDraw.bottom;
    //rcDraw.bottom += 1;
    //dc.FillSolidRect(rcDraw, RGB(0xea, 0xe9, 0xe1));

    dc.SetBkMode(TRANSPARENT);

    strFilePath = pDir->m_vCacheFiles[idx].strFilePath;
    strFile = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind(_T('\\')) - 1);
    strDir = strFilePath.Left(strFilePath.GetLength());

    // 绘制文件名
    hIconCache = g_IconCache.GetIcon(strFilePath);
    if (hIconCache)
    {
        hIcon = hIconCache;
    }
    else
    {
        hIcon = bigfilehelper::GetIconFromFilePath(strFilePath);
    }
    rcDraw = rcItem;
    rcDraw.left = nCurrentEnd;
    nCurrentEnd += GetColumnWidth(0);
    rcDraw.right = nCurrentEnd;
    if (rcDraw.Width() > 8)
    {
        dc.DrawIconEx(rcDraw.left + 4, rcDraw.top + (rcDraw.Height() - 16) / 2, hIcon, 16, 16);
    }
    if (rcDraw.Width() > 24)
    {
        rcDraw.left += 24;
        BOOL bFilter = CBigfileFilter::Instance().IsFileInFilter(strFilePath);
        BOOL bfilterEnable = GetSysFilterEnable();
        if(bFilter && bfilterEnable)
            dc.SetTextColor(RGB(0xcc, 0xcc, 0xcc));
        dc.DrawText(strFile, strFile.GetLength(), rcDraw, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_END_ELLIPSIS);
    }

    // 绘制进度条
    rcDraw.left = nCurrentEnd;
    nCurrentEnd += GetColumnWidth(1);
    rcDraw.right = nCurrentEnd;
    if (rcDraw.Width() > 8)
    {
        CString strSize;
        bigfilehelper::GetFileSizeString(pDir->m_vCacheFiles[idx].qwFileSize, strSize);
        dc.DrawText(strSize, strSize.GetLength(), rcDraw, DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
    }
//     if (rcDraw.Width() > 48)
//     {
//         CPen penBorder;
//         CBrush brushProgress;
//         CRect rcProgress = rcDraw;
//         int nLength;
//         rcProgress.left += 40;
//         rcProgress.right -= 4;
//         rcProgress.top += (rcDraw.Height() - 6) / 2;
//         rcProgress.bottom -= (rcDraw.Height() - 6) / 2;
//         penBorder.CreatePen(PS_SOLID, 1, RGB(0xb5, 0xb5, 0xb5));
//         brushProgress.CreateSolidBrush(RGB(0xf3, 0xf6, 0xfd));
//         dc.SelectPen(penBorder);
//         dc.SelectBrush(brushProgress);
//         dc.RoundRect(rcProgress, CPoint(3, 3));
//     }

    // 绘制路径
    rcDraw.left = nCurrentEnd;
    nCurrentEnd += GetColumnWidth(2);
    rcDraw.right = nCurrentEnd;

    if (rcDraw.Width() > 8)
    {
        dc.DrawText(strDir, strDir.GetLength(), rcDraw, DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);   
    }

    // 绘制控制
    rcDraw.left = nCurrentEnd;
    nCurrentEnd += GetColumnWidth(3);
    rcDraw.right = nCurrentEnd;

    if (rcDraw.Width() > 4)
    {
        CRect rcLink;
        for (size_t i = 0; i < m_vLinks.size(); ++i)
        {
            CString strLink = m_vLinks[i].strLink;
            rcLink = rcDraw;
            rcLink.left = rcDraw.left + 4 + 40 * (long)i;
            rcLink.top += 4;
            rcLink.bottom += 4;
            dc.SelectFont(underlineFont);
            dc.SetTextColor(RGB(0x4d, 0x70, 0x96));
            dc.DrawText(strLink, strLink.GetLength(), rcLink, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
            if (rcLink.right > rcDraw.right)
                rcLink.right = rcDraw.right;
            dc.DrawText(strLink, strLink.GetLength(), rcLink, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
            rcLink.top = (rcLink.top - m_nHeaderHeight) % m_nItemHeight;
            rcLink.bottom = (rcLink.bottom - m_nHeaderHeight) % m_nItemHeight;
            m_vLinks[i].rcLink = rcLink;
        }
    }

    // 绘制
    //dc.DrawText(strFilePath, strFilePath.GetLength(), rcDraw, DT_SINGLELINE|DT_VCENTER|DT_LEFT);

    if (hIcon != hIconCache)
    {
        DestroyIcon(hIcon);
    }
}