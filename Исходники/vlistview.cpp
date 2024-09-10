//*****************************************************************************
// "Courier New", 100, 0, EZ_ATTR_BOLD, 0, true) ;
void CVListView::set_listview_font(char * szFaceName, int iDeciPtHeight, unsigned iAttributes)
{
   TEXTMETRICA  txtm ;
   hdcSelf = GetDC(hwndVListView) ;
   hfont = EzCreateFont(hdcSelf, szFaceName, iDeciPtHeight, 0, iAttributes, 0, true) ;
   SelectObject(hdcSelf, hfont) ;
   // SetTextAlign(hdcSelf, TA_TOP | TA_LEFT) ; //  ??  probably not for listview
   GetTextMetricsA(hdcSelf, &txtm) ;
   cxChar =  txtm.tmAveCharWidth ;
   cyChar =  txtm.tmHeight + txtm.tmExternalLeading ;
   SendMessage (hwndVListView, WM_SETFONT, (WPARAM) hfont, TRUE) ;
}