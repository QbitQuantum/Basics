// TODO code: optimise airspace drawing (same as DrawAirSpace())
// draw airspace using alpha blending
//static 
void MapWindow::DrawTptAirSpace(LKSurface& Surface, const RECT& rc) {
  // since standard GDI functions (brushes, pens...) ignore alpha octet in ARGB 
  // color value and don't set it in the resulting bitmap, we cannot use
  // perpixel alpha blending, instead we use global opacity for alpha blend 
  // (same opacity for all pixels); for fully "transparent" areas (without 
  // airspace) we must copy destination bitmap into source bitmap first so that 
  // alpha blending of such areas results in the same pixels as origin pixels 
  // in destination 
  CAirspaceList::const_iterator it;
  CAirspaceList::const_reverse_iterator itr;
  const CAirspaceList& airspaces_to_draw = CAirspaceManager::Instance().GetNearAirspacesRef();
  int airspace_type;
  bool found = false;
  bool borders_only = (GetAirSpaceFillType() == asp_fill_ablend_borders);
  #if ASPOUTLINE
  #else
  bool outlined_only=(GetAirSpaceFillType()==asp_fill_border_only);
  #endif

  static bool asp_selected_flash = false;
  asp_selected_flash = !asp_selected_flash;
   
  int nDC1 = hdcbuffer.SaveState();
  int nDC2 = hdcMask.SaveState();
  int nDC3 = hdcTempAsp.SaveState();
#ifdef AIRSPACE_BORDER
DrawAirSpaceBorders(Surface, rc);
#endif
  // Draw airspace area
    if (1) {
    CCriticalSection::CGuard guard(CAirspaceManager::Instance().MutexRef());
    if (borders_only) {
       // Draw in reverse order!
       // The idea behind this, is lower top level airspaces are smaller. (statistically)
       // They have to be draw later, because inside border area have to be in correct color,
       // not the color of the bigger airspace above this small one.
      for (itr=airspaces_to_draw.rbegin(); itr != airspaces_to_draw.rend(); ++itr) {
            if ((*itr)->DrawStyle() == adsFilled) {
              airspace_type = (*itr)->Type();
              if (!found) {
                found = true;
                ClearTptAirSpace(Surface, rc);
              }
              // set filling brush
              hdcbuffer.SelectObject(GetAirSpaceSldBrushByClass(airspace_type));
              (*itr)->Draw(hdcbuffer, rc, true);
              (*itr)->Draw(hdcMask, rc, false);
            }
      }//for
    } else {
       // Draw in direct order!
      for (it=airspaces_to_draw.begin(); it != airspaces_to_draw.end(); ++it) {
            if ((*it)->DrawStyle() == adsFilled) {
              airspace_type = (*it)->Type();
              if (!found) {
                found = true;
                ClearTptAirSpace(Surface, rc);
              }
              // set filling brush
              hdcTempAsp.SelectObject(GetAirSpaceSldBrushByClass(airspace_type));
              (*it)->Draw(hdcTempAsp, rc, true);
            }
      }//for
    }//else borders_only
    }//mutex release

  // alpha blending
  if (found) {
    if (borders_only) {
        hdcTempAsp.CopyWithMask(
                rc.left,rc.top,
                rc.right-rc.left,rc.bottom-rc.top,
                hdcbuffer,rc.left,rc.top,
                hdcMask,rc.left,rc.top);
    }
    Surface.AlphaBlend(rc, hdcTempAsp, rc, (255 * GetAirSpaceOpacity()) / 100);
  }
  
  // draw it again, just the outlines
  
  // we will be drawing directly into given hdc, so store original PEN object
  LKPen hOrigPen = Surface.SelectObject(LK_WHITE_PEN);
#ifdef AIRSPACE_BORDER
  if(0)
#endif
    if (1) {
    CCriticalSection::CGuard guard(CAirspaceManager::Instance().MutexRef());
	for (it=airspaces_to_draw.begin(); it != airspaces_to_draw.end(); ++it) {
        if ((*it)->DrawStyle()) {
		  airspace_type = (*it)->Type();
#if ASPOUTLINE
if (bAirspaceBlackOutline ^ (asp_selected_flash && (*it)->Selected()) ) {
#else
if ( (((*it)->DrawStyle()==adsFilled)&&!outlined_only&&!borders_only) ^ (asp_selected_flash && (*it)->Selected()) ) {
#endif
			Surface.SelectObject(LK_BLACK_PEN);
		  } else
		   if(  (*it)->DrawStyle()==adsDisabled)   {
			Surface.SelectObject(LKPen_Grey_N2);
		   } else {
			Surface.SelectObject(hAirspacePens[airspace_type]);
		  }
#ifndef AIRSPACE_BORDER
   (*it)->Draw(hdc, rc, false);
#endif
        }
	}//for
    }

  // restore original PEN
  Surface.SelectObject(hOrigPen);
  
  hdcbuffer.RestoreState(nDC1);
  hdcMask.RestoreState(nDC2);    
  hdcTempAsp.RestoreState(nDC3);    
} // DrawTptAirSpace()