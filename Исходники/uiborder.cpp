//
/// This is a static function that performs the actual drawing of edges for a
/// UIBorder or an external client. It uses the system ::DrawEdge if available.
//
bool
TUIBorder::DrawEdge(TDC& dc, const TRect& frame, uint edge, uint flags)
{
  static int hasDrawEdge = true;

  // Try once to see if the API call is available. If not, do ourselves.
  //
  if (hasDrawEdge) {
    if (::DrawEdge(dc, (LPRECT)&frame, edge, flags))
      return true;
    if (::GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
      hasDrawEdge = false;
    else
      return false;
  }

  // ::DrawEdge is not available, do the drawing ourselves
  //
  TRect f(frame);  // working frame rectangle

  // If mono is set, draw a thin, flat, black (windowFrame) frame
  //
  if (flags & Mono) {
    if (edge & EdgeOuter) {
      PaintFrame(dc, f, flags, TColor::SysWindowFrame, TColor::SysWindowFrame);
      f.Inflate(-1,-1);
    }
    if (flags & Fill) { // !CQ repeated code--nest else?
      TBrush brsh(TColor::SysWindow);
      dc.SelectObject(brsh);
      dc.PatBlt(f);
      dc.RestoreBrush();
    }
    return true;
  }

  // If flat is set, draw a thin, flat, shadow frame
  //
  if (flags & Flat) {
    if (edge & EdgeOuter) {
      PaintFrame(dc, f, flags, TColor::Sys3dShadow, TColor::Sys3dShadow);
      f.Inflate(-1,-1);
    }
    if (flags & Fill) { // !CQ repeated code--nest else?
      TBrush brsh(TColor::Sys3dFace);
      dc.SelectObject(brsh);
      dc.PatBlt(f);
      dc.RestoreBrush();
    }
    return true;
  }

  // Draw outer edge if indicated, adjusting rect afterwards
  //
  if (edge & EdgeOuter) {
    static TColor tlColors[] = {
      TColor::Sys3dLight,       // EdgeRaised
      TColor::Sys3dHilight,     // EdgeRaised + Soft
      TColor::Sys3dShadow,      // EdgeSunken
      TColor::Sys3dDkShadow,    // EdgeSunken + Soft
    };
    static TColor brColors[] = {
      TColor::Sys3dDkShadow,    // EdgeRaised
      TColor::Sys3dDkShadow,    // EdgeRaised + Soft
      TColor::Sys3dHilight,     // EdgeSunken
      TColor::Sys3dHilight,     // EdgeSunken + Soft
    };
    int ci = ((edge & SunkenOuter) ? 2 : 0) | ((flags & Soft) ? 1 : 0);
    PaintFrame(dc, f, flags, tlColors[ci], brColors[ci]);
    f.Inflate(-1,-1);
  }

  // Draw inner edge if indicated, adjusting rect afterwards
  //
  if (edge & EdgeInner) {
    static TColor tlColors[] = {
      TColor::Sys3dHilight,     // EdgeRaised
      TColor::Sys3dLight,       // EdgeRaised + Soft
      TColor::Sys3dDkShadow,    // EdgeSunken
      TColor::Sys3dShadow,      // EdgeSunken + Soft
    };
    static TColor brColors[] = {
      TColor::Sys3dShadow,      // EdgeRaised
      TColor::Sys3dShadow,      // EdgeRaised + Soft
      TColor::Sys3dLight,       // EdgeSunken
      TColor::Sys3dLight,       // EdgeSunken + Soft
    };
    int ci = ((edge & SunkenOuter) ? 2 : 0) | ((flags & Soft) ? 1 : 0);
    PaintFrame(dc, f, flags, tlColors[ci], brColors[ci]);
    f.Inflate(-1,-1);
  }

  // Fill interior if indicated
  //
  if (flags & Fill) {
    TBrush brsh(TColor::Sys3dFace);
    dc.SelectObject(brsh);
    dc.PatBlt(f);
    dc.RestoreBrush();
  }

// !CQ not really usefull since frame is not returned
//  if (flags & Adjust)
//    frame = f;

  return true;
}