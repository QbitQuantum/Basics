 int TooltipManagerWin::CalcTooltipHeight()
 {
     // Ask the tooltip for it's font.
     int height;
     HFONT hfont = reinterpret_cast<HFONT>(
         SendMessage(tooltip_hwnd_, WM_GETFONT, 0, 0));
     if(hfont != NULL)
     {
         HDC dc = GetDC(tooltip_hwnd_);
         HFONT previous_font = static_cast<HFONT>(SelectObject(dc, hfont));
         int last_map_mode = SetMapMode(dc, MM_TEXT);
         TEXTMETRIC font_metrics;
         GetTextMetrics(dc, &font_metrics);
         height = font_metrics.tmHeight;
         // To avoid the DC referencing font_handle_, select the previous font.
         SelectObject(dc, previous_font);
         SetMapMode(dc, last_map_mode);
         ReleaseDC(NULL, dc);
     }
     else
     {
         // Tooltip is using the system font. Use gfx::Font, which should pick
         // up the system font.
         height = gfx::Font().GetHeight();
     }
     // Get the margins from the tooltip
     RECT tooltip_margin;
     SendMessage(tooltip_hwnd_, TTM_GETMARGIN, 0, (LPARAM)&tooltip_margin);
     return height + tooltip_margin.top + tooltip_margin.bottom;
 }