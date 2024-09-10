//
/// Sets the maximum horizontal extent for the list view window.
//
void
TListBoxView::SetExtent(const tstring& str)
{
  if (str.length() == 0)
    return;

  TClientDC  clientDC(*this);
  TSize extent = clientDC.GetTextExtent(str, str.length());
  extent.cx += 2; // room for focus rectangle

  if (extent.cx > MaxWidth)
    SetHorizontalExtent(MaxWidth = extent.cx);
}