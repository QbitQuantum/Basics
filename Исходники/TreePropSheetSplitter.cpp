void CTreePropSheetSplitter::UpdateParentRect(LPCRECT lpRectUpdate)
{
  GetParent()->RedrawWindow( lpRectUpdate, NULL, RDW_UPDATENOW | RDW_INVALIDATE );
}