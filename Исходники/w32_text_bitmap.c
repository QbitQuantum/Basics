      // Draw text to full-screen sized bitmap, cleared to <bgcolor>
      // Draw boxes for each word on EyeLink tracker display if <dotrack> set
      // Use font selected with get_new_font(), and draws it in <fgcolor>
      // RECT <margins> sets margins, and <lspace> sets pixels between lines
HBITMAP text_bitmap(char *txt, COLORREF fgcolor, COLORREF bgcolor, 
                               RECT margins, int lspace, int dotrack)
{
  HDC hdc;
  HBITMAP hbm;
  HDC mdc;
  HBRUSH oBrush;
  HBITMAP obm;

  hdc = GetDC(NULL);                 
  mdc = CreateCompatibleDC(hdc);     // create display-compatible memory context
  hbm = CreateCompatibleBitmap(hdc, SCRWIDTH, SCRHEIGHT);
  obm = SelectObject(mdc, hbm);      // create DDB bitmap, select into context
                                     
  oBrush = SelectObject(mdc, CreateSolidBrush(bgcolor | 0x02000000L));  // brush to fill with 
  PatBlt(mdc, 0, 0, SCRWIDTH, SCRHEIGHT, PATCOPY);                      // CLEAR BITMAP
  DeleteObject(SelectObject(mdc, oBrush));

  draw_text_box(mdc, txt, fgcolor, margins, lspace, dotrack);  // DRAW THE TEXT

  GdiFlush();     // ADDED for Wimdows 2000/XP: Forces drawing to be immediate      

  SelectBitmap(mdc, obm);     // Release the GDI resources
  DeleteDC(mdc);
  ReleaseDC(NULL, hdc);
  return hbm;                 // Return the new bitmap
}