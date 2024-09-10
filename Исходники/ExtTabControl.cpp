void ExtTabControl::DrawItem(LPDRAWITEMSTRUCT pdis)
{
    bool isBottom = (TCS_BOTTOM & GetStyle()) != 0;

    CRect rc = pdis->rcItem;
    int nTabIndex = pdis->itemID;
    bool fSelected = (nTabIndex == GetCurSel());
    ODA_DRAWENTIRE;
    char label[64];
    TCITEM tci;
    tci.mask = TCIF_TEXT | TCIF_PARAM;
    tci.pszText = label;
    tci.cchTextMax = ARRAYSIZE(label);
    if (GetItem(nTabIndex, &tci))
    {
        CDC dc;
        dc.Attach(pdis->hDC);

        CRect rcPadding(0, 0, 0, 0);
        CRect rcUsable = rc;
        rcUsable.left += 1;
        rcUsable.top += 1;
        if (fSelected)
        {
            rcUsable.OffsetRect(-1, -1);
            rcUsable.bottom++;
        }
        COLORREF accentColor = g_PaintManager->GetColor(COLOR_3DFACE);  // TODO
        COLORREF backgroundColor = g_PaintManager->GetColor(COLOR_3DFACE);
        CRect rcGradient = rcUsable;
        TRIVERTEX *vertices;
        int vertexCount;
        GRADIENT_RECT *gradRects;
        int gradRectCount;
        if (!fSelected)
        {
            backgroundColor = CExtBitmap::stat_HLS_Adjust(backgroundColor, 0.0, -0.14, 0.0);
            accentColor = CExtBitmap::stat_HLS_Adjust(accentColor, 0.0, -0.22, 0.0);

            int dx = rcGradient.Width() * 3 / 10;
            int dy = rcGradient.Height() * 3 / 10;

            // Blend between our main color and the background color for the top part of the gradient (so the gradient isn't so extreme)
            TRIVERTEX selectedVertices[3] =
            {
                { rcGradient.left, rcGradient.top, GetRValue(accentColor) * 256, GetGValue(accentColor) * 256, GetBValue(accentColor) * 256, 65280 },
                // -1 because using right again seems to cause some div by zero and mess up GDI
                { rcGradient.right - 1, rcGradient.top + dy, GetRValue(backgroundColor) * 256, GetGValue(backgroundColor) * 256, GetBValue(backgroundColor) * 256, 65280 },
                { rcGradient.right, rcGradient.bottom, GetRValue(backgroundColor) * 256, GetGValue(backgroundColor) * 256, GetBValue(backgroundColor) * 256, 65280 },
            };
            vertices = selectedVertices;
            vertexCount = ARRAYSIZE(selectedVertices);

            GRADIENT_RECT selectedGradRects[2] = { { 0, 1 }, { 1, 2 } };
            gradRects = selectedGradRects;
            gradRectCount = ARRAYSIZE(selectedGradRects);
        }
        else
        {
            backgroundColor = CExtBitmap::stat_HLS_Adjust(backgroundColor, 0.0, -0.12, 0.0);

            CPoint topLeft = rcGradient.TopLeft();
            CPoint bottomRight = rcGradient.BottomRight();
            if (!isBottom)
            {
                std::swap(topLeft, bottomRight);
            }
            // Blend between our main color and the background color for the top part of the gradient (so the gradient isn't so extreme)
            TRIVERTEX selectedVertices[2] =
            {
                { topLeft.x, topLeft.y, GetRValue(accentColor) * 256, GetGValue(accentColor) * 256, GetBValue(accentColor) * 256, 65280 },
                { bottomRight.x, bottomRight.y, GetRValue(backgroundColor) * 256, GetGValue(backgroundColor) * 256, GetBValue(backgroundColor) * 256, 65280 },
            };
            vertices = selectedVertices;
            vertexCount = ARRAYSIZE(selectedVertices);

            GRADIENT_RECT selectedGradRects[1] = { 0, 1 };
            gradRects = selectedGradRects;
            gradRectCount = ARRAYSIZE(selectedGradRects);
        }

        dc.FillSolidRect(rc, backgroundColor);

        // TODO: Turn these upside down if upside down...
        dc.GradientFill(vertices, vertexCount, gradRects, gradRectCount, GRADIENT_FILL_RECT_V);

        // Use a different font decoration depending on if this is the most recent version of this item.
        bool fNotMostRecent = false;

        rcUsable.OffsetRect(4, 1); // indent

        COLORREF crText = g_PaintManager->GetColor(fSelected ? COLOR_BTNTEXT : COLOR_BTNSHADOW);

        int nOldText = dc.SetTextColor(crText);
        int nOldBk = dc.SetBkMode(TRANSPARENT);
        dc.DrawText(tci.pszText, -1, &rcUsable, DT_SINGLELINE);
        dc.SetBkMode(nOldBk);
        dc.SetTextColor(nOldText);

        dc.Detach();
    }
}