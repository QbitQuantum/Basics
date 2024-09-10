static void
DrawBanner(Canvas &canvas, PixelRect &rc)
{
  const unsigned padding = 2;
  const Bitmap logo(IDB_LOGO);
  const unsigned banner_height = logo.GetHeight();

  /* draw the XCSoar logo */
  int x = rc.left + padding;
  canvas.Copy(x, rc.top + padding,
              logo.GetWidth(), logo.GetHeight(),
              logo, 0, 0);

  x += logo.GetWidth() + 8;

  canvas.Select(bold_font);
  canvas.SetTextColor(COLOR_BLACK);
  canvas.SetBackgroundTransparent();

  /* draw the XCSoar banner text with a larger font */
  Font large_font;
  large_font.LoadFile("/opt/xcsoar/share/fonts/VeraBd.ttf", 40);
  canvas.Select(large_font);
  const unsigned name_y = rc.top
    + (banner_height - large_font.GetHeight()) / 2;

  const TCHAR *const name1 = _T("XC");
  canvas.DrawText(x, name_y, name1);
  x += canvas.CalcTextWidth(name1);

  const TCHAR *const name2 = _T("Soar");
  canvas.SetTextColor(COLOR_GRAY);
  canvas.DrawText(x, name_y, name2);
  canvas.SetTextColor(COLOR_BLACK);
  x += canvas.CalcTextWidth(name2) + 30;

  /* some more text */
  const TCHAR *const website = _T("www.xcsoar.org");
  canvas.Select(normal_font);
  canvas.DrawText(x, rc.top + (banner_height - normal_font.GetHeight()) / 2,
                  website);

  const TCHAR *const comment = _T("powered off");
  canvas.DrawText(rc.right - canvas.CalcTextWidth(comment) - padding,
                  rc.top + padding, comment);

  rc.top += banner_height + 8;
}