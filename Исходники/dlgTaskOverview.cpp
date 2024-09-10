static void OnTaskPaintListItem(WindowControl * Sender, LKSurface& Surface){

  int n = UpLimit - LowLimit;
  TCHAR sTmp[120];
  TCHAR wpName[120];
  TCHAR landableStr[5] = TEXT(" [X]");
  // LKTOKEN _@M1238_ "L"
  landableStr[2] = MsgToken(1238)[0];
  LockTaskData();

  const PixelRect rcClient(Sender->GetClientRect());
  
  const int w0 = rcClient.GetSize().cx - DLGSCALE(1);
  const int w1 = Surface.GetTextWidth(TEXT(" 000km"));
  _stprintf(sTmp, _T("  000%s"), MsgToken(2179));
  const int w2 = Surface.GetTextWidth(sTmp);

  const int TextMargin = (rcClient.GetSize().cy - Surface.GetTextHeight(TEXT("A"))) / 2;

  const int p1 = w0-w1-w2- rcClient.GetSize().cy - DLGSCALE(2);
  const int p2 = w0-w2- rcClient.GetSize().cy - DLGSCALE(2);
  
  const PixelRect rc = {
      0, 
      0,
      rcClient.GetSize().cy, 
      rcClient.GetSize().cy
  };
  
  if (DrawListIndex < n){
    int i = LowLimit + DrawListIndex;
//    if ((WayPointList[Task[i].Index].Flags & LANDPOINT) >0)
//      MapWindow::DrawRunway(hDC,  &WayPointList[Task[i].Index],  rc, 3000,true);
    MapWindow::DrawTaskPicto(Surface, DrawListIndex,  rc, 2500);
    if (Task[i].Index>=0) {
      _stprintf(wpName, TEXT("%s%s"),
                WayPointList[Task[i].Index].Name,
                (WayPointList[Task[i].Index].Flags & LANDPOINT) ? landableStr : TEXT(""));

      if (AATEnabled && ValidTaskPoint(i+1) && (i>0)) {
        if (Task[i].AATType==0 || Task[i].AATType==3) {
          _stprintf(sTmp, TEXT("%s %.1f"),
                    wpName, Task[i].AATCircleRadius*DISTANCEMODIFY);
        } else {
          if(Task[i].AATType==2 && DoOptimizeRoute()) {
             _stprintf(sTmp, TEXT("%s %.1f/1"),
                    wpName, Task[i].PGConeSlope);
          } else {
             _stprintf(sTmp, TEXT("%s %.1f"),
                    wpName, Task[i].AATSectorRadius*DISTANCEMODIFY);
          }
        }
      } else {
        _stprintf(sTmp, TEXT("%s"), wpName);
      }

      Surface.SetBackgroundTransparent();
      Surface.SetTextColor(RGB_BLACK);
      Surface.DrawTextClip(rc.right + DLGSCALE(2), TextMargin, sTmp, p1-DLGSCALE(4));

      _stprintf(sTmp, TEXT("%.0f %s"),Task[i].Leg*DISTANCEMODIFY,Units::GetDistanceName());
      Surface.DrawText(rc.right+p1+w1-Surface.GetTextWidth(sTmp), TextMargin, sTmp);

      _stprintf(sTmp, TEXT("%d%s"),  iround(Task[i].InBound),MsgToken(2179));
      Surface.DrawText(rc.right +p2+w2-Surface.GetTextWidth(sTmp), TextMargin, sTmp);

    }

  } else {

    Surface.SetTextColor(RGB_BLACK);

     // if (DrawListIndex==n) { // patchout 091126
     if (DrawListIndex==n && UpLimit < MAXTASKPOINTS) { // patch 091126

	// LKTOKEN  _@M832_ = "add waypoint"
      _stprintf(sTmp, TEXT("  (%s)"), MsgToken(832));
      Surface.DrawText(rc.right +DLGSCALE(2), TextMargin, sTmp);
    } else if ((DrawListIndex==n+1) && ValidTaskPoint(0)) {

      if (!AATEnabled || ISPARAGLIDER) {
        // LKTOKEN  _@M735_ = "Total:"
        Surface.DrawText(rc.right +DLGSCALE(2), TextMargin, MsgToken(735));
	   _stprintf(sTmp, TEXT("%.0f %s%s"), lengthtotal*DISTANCEMODIFY, Units::GetDistanceName(), fai_ok?_T(" FAI"):_T(""));
	
       Surface.DrawText(rc.right +p1+w1-Surface.GetTextWidth(sTmp), TextMargin, sTmp);

      } else {

      double d1 = CALCULATED_INFO.TaskDistanceToGo;
      if ((CALCULATED_INFO.TaskStartTime>0.0) && (CALCULATED_INFO.Flying) && (ActiveTaskPoint>0)) {
                   d1 += CALCULATED_INFO.TaskDistanceCovered;
      }

	if (d1==0.0) {
	  d1 = CALCULATED_INFO.AATTargetDistance;
	}

	_stprintf(sTmp, TEXT("%s %.0f min %.0f (%.0f) %s"),
	// LKTOKEN  _@M735_ = "Total:"
                  MsgToken(735),
                  AATTaskLength*1.0,
		  DISTANCEMODIFY*lengthtotal,
		  DISTANCEMODIFY*d1,
		  Units::GetDistanceName());
	Surface.DrawText(rc.right +DLGSCALE(2), TextMargin, sTmp);
      }
    }
  }
  UnlockTaskData();

}