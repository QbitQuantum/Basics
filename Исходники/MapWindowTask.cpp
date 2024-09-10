void
MapWindow::DrawTaskOffTrackIndicator(Canvas &canvas)
{
  if (Calculated().circling 
      || !Basic().location_available
      || !Basic().track_available
      || !GetMapSettings().detour_cost_markers_enabled)
    return;

  const TaskStats &task_stats = Calculated().task_stats;
  const ElementStat &current_leg = task_stats.current_leg;

  if (!task_stats.task_valid || !current_leg.location_remaining.IsValid())
    return;

  const GeoPoint target = current_leg.location_remaining;
  GeoVector vec(Basic().location, target);

  if ((Basic().track - vec.bearing).AsDelta().AbsoluteDegrees() < fixed(10))
    // insignificant error
    return;

  fixed distance_max =
    std::min(vec.distance,
             render_projection.GetScreenDistanceMeters() * fixed(0.7));

  // too short to bother
  if (distance_max < fixed(5000))
    return;

  GeoPoint start = Basic().location;
  
  canvas.Select(*look.overlay_font);
  canvas.SetTextColor(COLOR_BLACK);
  canvas.SetBackgroundTransparent();
  
  GeoPoint dloc;
  int ilast = 0;
  for (fixed d = fixed(1) / 4; d <= fixed(1); d += fixed(1) / 4) {
    dloc = FindLatitudeLongitude(start, Basic().track, distance_max * d);
    
    fixed distance0 = start.Distance(dloc);
    fixed distance1 = target.Distance(dloc);
    fixed distance = fixed(distance0 + distance1) / vec.distance;
    int idist = iround((distance - fixed(1)) * 100);
    
    if ((idist != ilast) && (idist > 0) && (idist < 1000)) {
      TCHAR Buffer[5];
      _stprintf(Buffer, _T("%d"), idist);
      RasterPoint sc = render_projection.GeoToScreen(dloc);
      PixelSize tsize = canvas.CalcTextSize(Buffer);
      canvas.DrawText(sc.x - tsize.cx / 2, sc.y - tsize.cy / 2, Buffer);
      ilast = idist;
    }
  }
}