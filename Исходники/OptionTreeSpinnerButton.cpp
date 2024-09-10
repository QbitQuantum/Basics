void COptionTreeSpinnerButton::OnPaint()
{
    // Make sure options aren't NULL
    if (m_otSpinnerOption == NULL)
    {
        return;
    }

    // Declare variables
    CPaintDC dc(this);
    CDC* pDCMem = new CDC;
    CBitmap bpMem;
    CBitmap *bmOld;
    COLORREF crOld;
    HGDIOBJ hOldBrush;
    int nOldBack;
    CRect rcButtonTop, rcButtonBottom, rcClient;
    CString strText;
    HGDIOBJ hOld;

    // Get client rectangle
    GetClientRect(rcClient);

    // Calculate rectangle
    // -- Top
    rcButtonTop.top = rcClient.top;
    rcButtonTop.left = (rcClient.right - 2) - OT_SPINNER_WIDTH;
    rcButtonTop.right = rcClient.right - 2;
    rcButtonTop.bottom = rcClient.Height() / 2;
    m_rcButtonTop = rcButtonTop;
    // -- Bottom
    rcButtonBottom.top = rcButtonTop.bottom;
    rcButtonBottom.left = (rcClient.right - 2) - OT_SPINNER_WIDTH;
    rcButtonBottom.right = rcClient.right - 2;
    rcButtonBottom.bottom = rcClient.bottom;
    m_rcButtonBottom = rcButtonBottom;

    // Create DC
    pDCMem->CreateCompatibleDC(&dc);

    // Create bitmap
    bpMem.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());

    // Select bitmap
    bmOld = pDCMem->SelectObject(&bpMem);

    // Set background mode
    nOldBack = pDCMem->SetBkMode(TRANSPARENT);

    // Set text color
    crOld = pDCMem->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));

    // Select font
    hOld = pDCMem->SelectObject(m_otSpinnerOption->GetNormalFont());

    // Draw control background
    hOldBrush = pDCMem->SelectObject(GetSysColorBrush(COLOR_BTNFACE));
    pDCMem->PatBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), PATCOPY);

    // Wrap around
    if (GetOption(OT_EDIT_WRAPAROUND) == TRUE)
    {
        // -- Draw top button
        // -- -- Pressed
        if (m_bTopPressed == TRUE)
        {
            pDCMem->DrawFrameControl(&rcButtonTop, DFC_SCROLL, DFCS_PUSHED | DFCS_SCROLLUP);
        }
        // -- -- UnPressed
        else
        {
            pDCMem->DrawFrameControl(&rcButtonTop, DFC_SCROLL, DFCS_SCROLLUP);
        }

        // -- Draw bottom button
        // -- -- Pressed
        if (m_bBottomPressed == TRUE)
        {
            pDCMem->DrawFrameControl(&rcButtonBottom, DFC_SCROLL, DFCS_PUSHED | DFCS_SCROLLDOWN);
        }
        // -- -- UnPressed
        else
        {
            pDCMem->DrawFrameControl(&rcButtonBottom, DFC_SCROLL, DFCS_SCROLLDOWN);
        }
    }
    // No Wrap around
    else
    {
        // -- Draw top button
        if (_GetValue() >= m_dRangeTop)
        {
            pDCMem->DrawFrameControl(&rcButtonTop, DFC_SCROLL, DFCS_INACTIVE | DFCS_SCROLLUP);
        }
        else
        {
            // -- -- Pressed
            if (m_bTopPressed == TRUE)
            {
                pDCMem->DrawFrameControl(&rcButtonTop, DFC_SCROLL, DFCS_PUSHED | DFCS_SCROLLUP);
            }
            // -- -- UnPressed
            else
            {
                pDCMem->DrawFrameControl(&rcButtonTop, DFC_SCROLL, DFCS_SCROLLUP);
            }
        }

        // -- Draw bottom button
        if (_GetValue() <= m_dRangeBottom)
        {
            pDCMem->DrawFrameControl(&rcButtonBottom, DFC_SCROLL, DFCS_INACTIVE | DFCS_SCROLLDOWN);
        }
        else
        {
            // -- -- Pressed
            if (m_bBottomPressed == TRUE)
            {
                pDCMem->DrawFrameControl(&rcButtonBottom, DFC_SCROLL, DFCS_PUSHED | DFCS_SCROLLDOWN);
            }
            // -- -- UnPressed
            else
            {
                pDCMem->DrawFrameControl(&rcButtonBottom, DFC_SCROLL, DFCS_SCROLLDOWN);
            }
        }
    }

    // Copy to screen
    dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pDCMem, 0, 0, SRCCOPY);

    // Restore GDI ojects
    pDCMem->SelectObject(bmOld);
    pDCMem->SelectObject(hOldBrush);
    pDCMem->SetBkMode(nOldBack);
    pDCMem->SelectObject(hOld);
    pDCMem->SetTextColor(crOld);

    // Delete objects
    if (pDCMem->GetSafeHdc() != NULL)
    {
        pDCMem->DeleteDC();
    }
    delete pDCMem;
    if (bpMem.GetSafeHandle() != NULL)
    {
        bpMem.DeleteObject();
    }
}