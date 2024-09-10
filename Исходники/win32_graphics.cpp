void Win32Graphics::fillRect( int left, int top, int width, int height,
                              uint32_t color )
{
    // Update the mask with the rectangle area
    HRGN newMask = CreateRectRgn( left, top, left + width, top + height );
    CombineRgn( m_mask, m_mask, newMask, RGN_OR );
    SelectClipRgn( m_hDC, m_mask );
    DeleteObject( newMask );

    // Create a brush with the color
    int red = (color & 0xff0000) >> 16;
    int green = (color & 0xff00) >> 8;
    int blue = color & 0xff;
    HBRUSH hBrush = CreateSolidBrush( RGB( red, green, blue ) );

    // Draw the rectangle
    RECT r;
    r.left = left;
    r.top = top;
    r.right = left + width;
    r.bottom = top + height;
    FillRect( m_hDC, &r, hBrush );
    DeleteObject( hBrush );
}