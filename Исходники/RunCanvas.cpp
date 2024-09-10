  void paint(Canvas &canvas) {
    canvas.SelectHollowBrush();
    canvas.SelectBlackPen();

    Brush red_brush(COLOR_RED);

    const PixelRect rc = GetClientRect();
    const int width = rc.right - rc.left;
    const int height = rc.bottom - rc.top;
    const int hmiddle = (rc.left + rc.right) / 2;
    const int vmiddle = (rc.top + rc.bottom) / 2;

    RasterPoint p1[3] = {
      { -100, vmiddle },
      { (width * 2) / 3, -100 },
      { hmiddle, height * 2 },
    };

    RasterPoint p2[3] = {
      { -2000, vmiddle },
      { width * 10, -3000 },
      { width * 5, 3000 },
    };

    const TCHAR *label;
    switch (page) {
    case 0:
      canvas.DrawSegment(hmiddle, vmiddle,
                     min(width, height) / 3,
                     Angle::Zero(), Angle::Degrees(90),
                     false);
      label = _T("segment 0-90 horizon=false");
      break;

    case 1:
      canvas.DrawSegment(hmiddle, vmiddle,
                     min(width, height) / 3,
                     Angle::Degrees(45), Angle::Degrees(180),
                     true);
      label = _T("segment 45-180 horizon=true");
      break;

    case 2:
      canvas.DrawCircle(hmiddle, vmiddle,
                    min(width, height) / 3);
      label = _T("circle");
      break;

    case 3:
    case 4:
      PixelRect rc;
      rc.left = hmiddle - 50;
      rc.top = vmiddle - 20;
      rc.right = hmiddle + 50;
      rc.bottom = vmiddle + 20;
      canvas.DrawButton(rc, page == 4);
      label = page == 4
        ? _T("button down=true") : _T("button down=false");
      break;

    case 5:
      canvas.Select(red_brush);
      canvas.DrawPolygon(p1, 3);
      label = _T("big polygon");
      break;

    case 6:
      canvas.Select(red_brush);
      canvas.DrawPolygon(p2, 3);
      label = _T("huge polygon");
      break;
    }

    canvas.SetTextColor(Color(0, 0, 128));
    canvas.SetBackgroundTransparent();
    canvas.Select(normal_font);
    canvas.DrawText(5, 5, label);
#ifndef ENABLE_OPENGL
    canvas.DrawText(5, 25,
                    buffered ? _T("buffered") : _T("not buffered"));
#endif
  }