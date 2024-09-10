void TextProgressCtrl::OnPaint(void)
{
    CPaintDC sPaintDC(this);

    MemDC sMemDC(&sPaintDC);

    CRect sClientRect;
    GetClientRect(sClientRect);

    xpr_double_t sFraction = 0.0;
    if ((mMax - mMin) > 0)
        sFraction = (xpr_double_t)(mPos - mMin) / ((xpr_double_t)(mMax - mMin));

    CRect sProgressRect(sClientRect);
    sProgressRect.right = sProgressRect.left + (xpr_sint_t)(sProgressRect.Width() * sFraction);

    CRect sBackRect(sClientRect);
    sBackRect.left = sProgressRect.right;

    sMemDC.FillSolidRect(sProgressRect, mProgressColor);
    sMemDC.FillSolidRect(sBackRect, mBackColor);

    if (XPR_IS_TRUE(mShowText))
    {
        xpr_tchar_t sText[0xff] = {0};
        _stprintf(sText, XPR_STRING_LITERAL("%d%%"), (xpr_sint_t)(sFraction * 100.0));

        CFont *sOldFont = sMemDC.SelectObject(&mTextFont);
        sMemDC.SetBkMode(TRANSPARENT);

        CRgn sRgn;
        sRgn.CreateRectRgn(sProgressRect.left, sProgressRect.top, sProgressRect.right, sProgressRect.bottom);
        sMemDC.SelectClipRgn(&sRgn);
        sMemDC.SetTextColor(mTextBackColor);

        sMemDC.DrawText(sText, sClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        sRgn.DeleteObject();
        sRgn.CreateRectRgn(sBackRect.left, sBackRect.top, sBackRect.right, sBackRect.bottom);
        sMemDC.SelectClipRgn(&sRgn);
        sMemDC.SetTextColor(mTextProgressColor);

        sMemDC.DrawText(sText, sClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        sMemDC.SelectObject(sOldFont);
    }
}