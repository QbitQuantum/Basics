void GuideControl::OnPaint()
{
    CStatic::OnPaint();

    CDC* dc = GetDC();
    if (!dc)
        return;

    BITMAP markInfo;
    uploadDone_.GetBitmap(&markInfo);

    CRect rect;
    GetClientRect(&rect);

    CDC markDc;
    markDc.CreateCompatibleDC(dc);

    CGdiObject* o = markDc.SelectObject(&uploadDone_);

    dc->MaskBlt(0, 0, markInfo.bmWidth, markInfo.bmHeight, &markDc, 0, 0,
                uploadDoneMask_, 0, 0, MAKEROP4(SRCPAINT, SRCCOPY));

    markDc.SelectObject(&uploadFailed_);
    dc->MaskBlt(170, 0, markInfo.bmWidth, markInfo.bmHeight, &markDc, 0, 0,
                uploadFailedMask_, 0, 0, MAKEROP4(SRCPAINT, SRCCOPY));

    markDc.SelectObject(o);

    ReleaseDC(dc);
}