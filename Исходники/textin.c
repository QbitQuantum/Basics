static void CalculateWindowHeight(void)
{
   HDC hdc = GetDC(GetDesktopWindow());
   int oldMapMode = SetMapMode(hdc,MM_TEXT);
   HFONT hOldFont = (HFONT) SelectObject(hdc,GetFont(FONT_INPUT));
   TEXTMETRIC tm;

   GetTextMetrics(hdc,&tm);
   inputHeight = tm.tmHeight + tm.tmInternalLeading;
   SelectObject(hdc,hOldFont);
   SetMapMode(hdc,oldMapMode);
   ReleaseDC(GetDesktopWindow(),hdc);
}