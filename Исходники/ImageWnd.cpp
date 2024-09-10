int CImageWnd::GetScrollPos(int nBar)
{
   SCROLLINFO scrollInfo = { 0 };

   scrollInfo.cbSize = sizeof(SCROLLINFO);
   scrollInfo.fMask = SIF_POS;

   // Get current position
   GetScrollInfo(nBar, &scrollInfo);

   return scrollInfo.nPos;
}