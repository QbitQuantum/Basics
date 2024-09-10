bool MapWindow::TextInBox(LKSurface& Surface, const RECT *clipRect,  const TCHAR* Value, int x, int y,
                          TextInBoxMode_t *Mode, bool noOverlap) {

  SIZE tsize;
  RECT brect;
  LKSurface::OldFont oldFont {};
  bool drawn=false;

  if ((x<clipRect->left-WPCIRCLESIZE) ||
      (x>clipRect->right+(WPCIRCLESIZE*3)) ||
      (y<clipRect->top-WPCIRCLESIZE) ||
      (y>clipRect->bottom+WPCIRCLESIZE)) {
    return drawn;
  }

  if (Mode == NULL) return false;

  const auto hbOld = Surface.SelectObject(LKBrush_White);
  const auto hpOld = Surface.SelectObject(LK_BLACK_PEN);

  if (Mode->Reachable){
    if (Appearance.IndLandable == wpLandableDefault){
      x += 5;  // make space for the green circle
    }else
      if (Appearance.IndLandable == wpLandableAltA){
	x += 0;
      }
  }

  // landable waypoint label inside white box
  if (!Mode->NoSetFont) {
    if (Mode->Border || Mode->WhiteBold){
      oldFont = Surface.SelectObject(MapWaypointBoldFont);
    } else {
      oldFont = Surface.SelectObject(MapWaypointFont);
    }
  }

  Surface.GetTextSize(Value, &tsize);

  if (Mode->AlligneRight){
    x -= tsize.cx;
  } else
    if (Mode->AlligneCenter){
      x -= tsize.cx/2;
      y -= tsize.cy/2;
    }

  bool notoverlapping = true;

  if (Mode->Border || Mode->WhiteBorder){

    POINT offset;

    brect.left = x-2;
    brect.right = brect.left+tsize.cx+4;
    brect.top = y+((tsize.cy+4)>>3)-2;
    brect.bottom = brect.top+3+tsize.cy-((tsize.cy+4)>>3);

    if (Mode->AlligneRight)
      x -= 3;

    if (TextInBoxMoveInView(clipRect, &offset, &brect)){
      x += offset.x;
      y += offset.y;
    }

    #if CLIP_TEXT
    if (y>=clipRect->bottom || brect.bottom>=clipRect->bottom ) return false;
    #endif

	notoverlapping = checkLabelBlock(&brect);


    if (!noOverlap || notoverlapping) {
      LKSurface::OldPen oldPen;
      if (Mode->Border) {
        oldPen = Surface.SelectObject(LKPen_Black_N1);
      } else {
        oldPen = Surface.SelectObject(LK_WHITE_PEN);
      }
      Surface.RoundRect(brect, NIBLSCALE(4), NIBLSCALE(4));
      Surface.SelectObject(oldPen);
      if (Mode->SetTextColor) Surface.SetTextColor(Mode->Color); else Surface.SetTextColor(RGB_BLACK);
#ifndef __linux__
      Surface.DrawText(x, y, Value);
#else
      Surface.DrawText(x, y+NIBLSCALE(1), Value);
#endif
      drawn=true;
    }


  } else if (Mode->FillBackground) {