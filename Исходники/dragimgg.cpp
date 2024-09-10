// Override this if you are using a virtual image (drawing your own image)
bool wxGenericDragImage::DoDrawImage(wxDC& dc, const wxPoint& pos) const
{
    if (m_bitmap.IsOk())
    {
        dc.DrawBitmap(m_bitmap, pos.x, pos.y, (m_bitmap.GetMask() != 0));
        return true;
    }
    else if (m_icon.IsOk())
    {
        dc.DrawIcon(m_icon, pos.x, pos.y);
        return true;
    }
    else
        return false;
}