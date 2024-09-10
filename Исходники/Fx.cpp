Bool CFx::IsObjectInRect(wxRect& Rect)
{
    return (Rect.Intersects(*_pFxRect) || Rect.Intersects(*_pFxStateRect));
}