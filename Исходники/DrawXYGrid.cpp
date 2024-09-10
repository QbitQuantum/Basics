void Statistics::DrawXGrid(LKSurface& Surface, const RECT& rc,
			   const double tic_step, 
			   const double zero,
                           const int Style, 
			   const double unit_step, bool draw_units) {

  if(INVERTCOLORS)
    Surface.SelectObject(LK_BLACK_PEN);


  POINT line[2];

  double xval;
  SIZE tsize;

  int xmin, ymin, xmax, ymax;
  if (!tic_step) return;
  LKASSERT(tic_step!=0);

  //  bool do_units = ((x_max-zero)/tic_step)<10;

  for (xval=zero; xval<= x_max; xval+= tic_step) {

    xmin = (int)((xval-x_min)*xscale)+rc.left+BORDER_X;
    ymin = rc.top;
    xmax = xmin;
    ymax = rc.bottom;
    line[0].x = xmin;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax-BORDER_Y;

    // STYLE_THINDASHPAPER
    if ((xval< x_max) 
        && (xmin>=rc.left+BORDER_X) && (xmin<=rc.right)) {
      StyleLine(Surface, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, xval*unit_step/tic_step, unit_step);

//	SetBkMode(hdc, OPAQUE);
	Surface.GetTextSize(unit_text, _tcslen(unit_text), &tsize);
	Surface.DrawText(xmin-tsize.cx/2, ymax-tsize.cy, unit_text, _tcslen(unit_text));
	Surface.SetBkMode(TRANSPARENT);
      }
    }

  }

  for (xval=zero-tic_step; xval>= x_min; xval-= tic_step) {

    xmin = (int)((xval-x_min)*xscale)+rc.left+BORDER_X;
    ymin = rc.top;
    xmax = xmin;
    ymax = rc.bottom;
    line[0].x = xmin;
    line[0].y = ymin;
    line[1].x = xmax;
    line[1].y = ymax-BORDER_Y;

    // STYLE_THINDASHPAPER

    if ((xval> x_min) 
        && (xmin>=rc.left+BORDER_X) && (xmin<=rc.right)) {

      StyleLine(Surface, line[0], line[1], Style, rc);

      if (draw_units) {
	TCHAR unit_text[MAX_PATH];
	FormatTicText(unit_text, xval*unit_step/tic_step, unit_step);
//	SetBkMode(hdc, OPAQUE);
	Surface.GetTextSize(unit_text, _tcslen(unit_text), &tsize);
	Surface.DrawText(xmin-tsize.cx/2, ymax-tsize.cy, unit_text, _tcslen(unit_text));
	Surface.SetBkMode(TRANSPARENT);
      }
    }

  }

}