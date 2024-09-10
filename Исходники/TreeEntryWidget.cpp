void TreeEntryWidget::PaintBufferPre(HWND, HDC dc, int width, int height)
{
    SelectObject(dc, GetStockObject(DC_PEN));
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, brush);
    SetDCPenColor(dc, pen);
    Rectangle(dc, 0, 0, width, height);
    SetDCBrushColor(dc, 0x00e3d9e4);
    Rectangle(dc, 3, 3, width - 3 , height - 3);
}