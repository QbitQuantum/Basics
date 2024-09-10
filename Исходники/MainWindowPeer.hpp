 virtual void DrawWhiteText
 (HDC dc, RECT& rect, const char* text, int flags)
 {
     HGDIOBJ oldFont = SelectObject(dc, GetDefaultFont());
     SetTextColor(dc, RGB(0xff, 0xff, 0xff));
     SetBkMode(dc, TRANSPARENT);
     DrawTextA(dc, text, -1, &rect, flags);
     SelectObject(dc, oldFont);
 }