void CWebkitUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
    if ((hDC == NULL) || (raster_ == NULL) || (bitmap_bits_ == NULL) || !finish_layout_)
        return;

    if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;

    if (did_first_layout_ && bitmap_bits_ != NULL && finish_layout_)
    {
        for (int i = 0; i < bitmap_header_info_.biHeight; ++i)
        {
            memcpy_s(bitmap_bits_ + (bitmap_header_info_.biWidth * i * 4), \
                     bitmap_header_info_.biSizeImage / bitmap_header_info_.biHeight, \
                     (LPBYTE)view_->GetSurface()->GetData() + (bitmap_header_info_.biWidth * i * 4), \
                     (bitmap_header_info_.biWidth * 4));
        }
    }
    else if (bitmap_bits_ != NULL)
    {
        DWORD dwScreenX = GetSystemMetrics(SM_CXSCREEN);
        DWORD dwScreenY = GetSystemMetrics(SM_CYSCREEN);
        dwScreenX = static_cast<DWORD>((dwScreenX + 3) / 4 * 4);
        memset(bitmap_bits_, 0xFF, dwScreenX * dwScreenY * 4);
    }

    ::SetStretchBltMode(hDC, COLORONCOLOR);
    BITMAPINFOHEADER bmiHeader = bitmap_header_info_;
    bmiHeader.biHeight = -bmiHeader.biHeight;
    StretchDIBits(hDC, m_rcItem.left, m_rcItem.top, m_rcItem.right - m_rcItem.left, m_rcItem.bottom - m_rcItem.top,
                  0, 0, bitmap_header_info_.biWidth, bitmap_header_info_.biHeight, bitmap_bits_, (LPBITMAPINFO)&bmiHeader, DIB_RGB_COLORS, SRCCOPY);
}