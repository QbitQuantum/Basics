void CQueView::OnDraw(CDC* pDC)
{
    CDrawDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    CBitmap bitmap;
    CBitmap *pOldBitmap;

    // only paint the rect that needs repainting
    CRect client;
    pDC->GetClipBox(client);
    CRect rect;
    GetClientRect(&rect);

    CDC bitmapDC;
    auto pDrawDC = pDC;
    // draw to offscreen bitmap for fast looking repaints
    if (bitmapDC.CreateCompatibleDC(pDC)) {
        if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height())) {
            OnPrepareDC(&bitmapDC, nullptr);
            pDrawDC = &bitmapDC;

            // offset origin more because bitmap is just piece of the whole drawing
            //..,,	dc.OffsetViewportOrg(-rect.left, -rect.top);
            bitmapDC.OffsetViewportOrg(-rect.left, -rect.top);
            pOldBitmap = bitmapDC.SelectObject(&bitmap);

            // might as well clip to the same rectangle
            bitmapDC.IntersectClipRect(client);
        }
    }

    // paint background
    CBrush brush;
    if (!brush.CreateStockObject(WHITE_BRUSH))
        return;

    pDrawDC->FillRect(client, &brush);

    pDoc->DrawQue(pDrawDC, this);

    if (pDrawDC != pDC) {
        pDC->SetMapMode(MM_TEXT);
        bitmapDC.SetMapMode(MM_TEXT);
        pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), pDrawDC, 0, 0, SRCCOPY);
        bitmapDC.SelectObject(pOldBitmap);
    }
}