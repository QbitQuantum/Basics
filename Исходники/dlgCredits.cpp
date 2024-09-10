static void
OnLogoPaint(gcc_unused WndOwnerDrawFrame *Sender, Canvas &canvas)
{
  const UPixelScalar width = canvas.GetWidth();
  PixelScalar x = Layout::FastScale(10), y = x;

  canvas.ClearWhite();

  Bitmap title(width > 360 ? IDB_TITLE_HD : IDB_TITLE);

  // Determine title image size
  PixelSize title_size = title.GetSize();

  // Draw 'XCSoar N.N' title
  canvas.Copy(x, y, title_size.cx, title_size.cy, title, 0, 0);
  y += title_size.cy + Layout::FastScale(20);

  Font font;
  font.Load(GetStandardFontFace(), Layout::FastScale(16));
  canvas.Select(font);
  canvas.SetTextColor(COLOR_BLACK);
  canvas.SetBackgroundTransparent();

  canvas.DrawText(x, y, _T("version: "));
  canvas.DrawText(x + Layout::FastScale(80), y, XCSoar_VersionString);
  y += Layout::FastScale(22);

  canvas.DrawText(x, y, _T("date: "));
  canvas.DrawText(x + Layout::FastScale(80), y, _T(__DATE__));
#ifdef GIT_COMMIT_ID
  y += Layout::FastScale(22);

  canvas.DrawText(x, y, _T("git: "));
  canvas.DrawText(x + Layout::FastScale(80), y, _T(GIT_COMMIT_ID));
#endif
  y += Layout::FastScale(37);

  canvas.DrawText(x, y, _T("more information at"));
  y += Layout::FastScale(22);

  canvas.SetTextColor(COLOR_XCSOAR);
  canvas.DrawText(x, y, _T("http://www.xcsoar.org"));
}