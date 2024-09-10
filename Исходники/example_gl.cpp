static void myDrawAxesSprite( const ON_Viewport& viewport, HDC hdc )
{
  // Use simple Windows calls to draw world axes sprite in lower left corner.
  // Note that Windows has screen (0,0) in the upper left corner; i.e,
  // screen "y" increases downwards.
  if ( !hdc )
    return;
  const int axes_size = 30;

  int port_left, port_right, port_top, port_bottom;
  if ( !viewport.GetScreenPort( &port_left, &port_right, &port_bottom, &port_top, NULL, NULL ) )
    return;
  const int scr_width  = port_right - port_left; // no "+1" here
  const int scr_height = port_bottom - port_top; // no "+1" here

  if (4*axes_size >= scr_width )
    return;
  if (4*axes_size >= scr_height )
    return;

  int x0 = 3*axes_size/2;
  int y0 = port_bottom - 3*axes_size/2;
  int indx[3] = {0,1,2};
  double scr_coord[3][2];
  viewport.GetCoordinateSprite( axes_size, x0, y0, indx, scr_coord );

#define LXSIZE 3
#define LYSIZE 3
#define LOFF 3

  // draw 3 axes from back to front
  HPEN axis_pen[3];
  axis_pen[0] = CreatePen( PS_SOLID, 2, RGB(255,0,0) );
  axis_pen[1] = CreatePen( PS_SOLID, 2, RGB(0,255,0) );
  axis_pen[2] = CreatePen( PS_SOLID, 2, RGB(0,0,255) );
  HGDIOBJ saved_pen = SelectObject( hdc, axis_pen[0] );

  int i, k, x, y, lx, ly;
  for (i=0;i<3;i++) {
    k = indx[i];
    x = (int)scr_coord[k][0];
    y = (int)scr_coord[k][1];
    // use direction of screen vector to determine letter placement
    lx = x-x0; ly = y-y0;
    if (abs(lx) > abs(ly)) {
      // center letter to right/left of axis end
      lx = (x >= x0) ? x + LXSIZE+LOFF : x - LXSIZE-LOFF;
      ly = y;
    }
    else if (abs(ly) > abs(lx)) {
      // center letter above/below axis end
      lx = x;
      ly = (y >= y0) ? y + LYSIZE+LOFF : y - LYSIZE-LOFF;
    }
    else if (lx) {
      // diagonal axis - center letter on axis
      lx = (x >= x0) ? x + LXSIZE+LOFF : x - LXSIZE-LOFF;
      ly = (y >= y0) ? y + LYSIZE+LOFF : y - LYSIZE-LOFF;
    }
    else {
      // axis is perp to screen - center letter at axis end
      lx = x;
      ly = y;
    }
    SelectObject( hdc, axis_pen[k] );

    // draw axis
    MoveToEx( hdc, x0, y0, NULL );
    LineTo( hdc, x, y );

    // draw axis label
    switch (k) {
    case 0: // X
      MoveToEx( hdc, lx-LXSIZE, ly-LYSIZE, NULL );
      LineTo(   hdc, lx+LXSIZE, ly+LYSIZE );
      MoveToEx( hdc, lx-LXSIZE, ly+LYSIZE, NULL );
      LineTo(   hdc, lx+LXSIZE, ly-LYSIZE );
      break;
    case 1: // Y
      MoveToEx( hdc, lx-LXSIZE, ly-LYSIZE, NULL );
      LineTo(   hdc, lx,    ly    );
      LineTo(   hdc, lx+LXSIZE, ly-LYSIZE );
      MoveToEx( hdc, lx,    ly, NULL    );
      LineTo(   hdc, lx,    ly+LYSIZE );
      break;
    case 2: // Z
      MoveToEx( hdc, lx-LXSIZE, ly-LYSIZE, NULL );
      LineTo(   hdc, lx+LXSIZE, ly-LYSIZE );
      LineTo(   hdc, lx-LXSIZE, ly+LYSIZE );
      LineTo(   hdc, lx+LXSIZE, ly+LYSIZE );
      break;
    }

  }
  SelectObject( hdc, saved_pen );
  DeleteObject( axis_pen[0] );
  DeleteObject( axis_pen[1] );
  DeleteObject( axis_pen[2] );

#undef LXSIZE
#undef LYSIZE
#undef LOFF

}