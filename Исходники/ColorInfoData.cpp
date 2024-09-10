wxImage ColorInfoData::UIImage(const ColorType type, const wxSize &size)
{
    wxASSERT((0 <= type) && (CR_SIZE > type));

    checkColors();

    //now fill it with the color requested
    wxColour color = UIColor(type);
    wxColour border = GLColor(type);

    // Create a transparent border so it's not just a blob of color.
    wxColour transparent = SKIN.Element(shIconTransparent);

    // The easiest way to do this is to just create a memory bitmap and draw
    // into it.
    wxBitmap bitmap(size.x, size.y);
    wxMemoryDC dc;
    dc.SelectObject(bitmap);

    // Transparent outline.
    dc.SetBrush(wxBrush(transparent));
    dc.SetPen(wxPen(transparent));
    dc.DrawRectangle(0, 0, size.x, size.y);

    // Border.
    dc.SetBrush(wxBrush(border));
    dc.SetPen(wxPen(border));
    dc.DrawRectangle(1, 1, size.x - 2, size.y - 2);

    // Color.
    dc.SetBrush(wxBrush(color));
    dc.SetPen(wxPen(color));
    dc.DrawRectangle(2, 2, size.x - 4, size.y - 4);

    dc.SelectObject(wxNullBitmap);
    return bitmap.ConvertToImage();
}