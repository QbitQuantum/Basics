void
TaskEditPanel::OnPaintItem(Canvas &canvas, const PixelRect rc,
                           unsigned DrawListIndex)
{
  assert(DrawListIndex <= ordered_task->TaskSize());

  const PixelScalar line_height = rc.bottom - rc.top;

  TCHAR buffer[120];

  const Font &name_font = *dialog.GetLook().list.font_bold;
  const Font &small_font = *dialog.GetLook().small_font;

  // Draw "Add turnpoint" label
  if (DrawListIndex == ordered_task->TaskSize()) {
    canvas.Select(name_font);
    canvas.SetTextColor(COLOR_BLACK);
    _stprintf(buffer, _T("  (%s)"), _("Add Turnpoint"));
    canvas.DrawText(rc.left + line_height + Layout::FastScale(2),
                    rc.top + line_height / 2 - name_font.GetHeight() / 2,
                    buffer);
    return;
  }

  const OrderedTaskPoint &tp = ordered_task->GetTaskPoint(DrawListIndex);
  GeoVector leg = tp.GetNominalLegVector();
  bool show_leg_info = leg.distance > fixed(0.01);

  // Draw icon
  const RasterPoint pt(rc.left + line_height / 2,
                       rc.top + line_height / 2);

  PixelScalar radius = std::min(PixelScalar(line_height / 2
                                            - Layout::FastScale(4)),
                                Layout::FastScale(10));

  OZPreviewRenderer::Draw(canvas, tp.GetObservationZone(),
                          pt, radius, task_look,
                          CommonInterface::GetMapSettings().airspace,
                          airspace_look);

  // Y-Coordinate of the second row
  PixelScalar top2 = rc.top + name_font.GetHeight() + Layout::FastScale(4);

  // Use small font for details
  canvas.Select(small_font);
  canvas.SetTextColor(COLOR_BLACK);

  UPixelScalar leg_info_width = 0;
  if (show_leg_info) {
    // Draw leg distance
    FormatUserDistanceSmart(leg.distance, buffer, true);
    UPixelScalar width = leg_info_width = canvas.CalcTextWidth(buffer);
    canvas.DrawText(rc.right - Layout::FastScale(2) - width,
                    rc.top + Layout::FastScale(2) +
                    (name_font.GetHeight() - small_font.GetHeight()) / 2,
                    buffer);

    // Draw leg bearing
    FormatBearing(buffer, ARRAY_SIZE(buffer), leg.bearing);
    width = canvas.CalcTextWidth(buffer);
    canvas.DrawText(rc.right - Layout::FastScale(2) - width, top2, buffer);

    if (width > leg_info_width)
      leg_info_width = width;

    leg_info_width += Layout::FastScale(2);
  }

  // Draw details line
  PixelScalar left = rc.left + line_height + Layout::FastScale(2);
  OrderedTaskPointRadiusLabel(tp.GetObservationZone(), buffer);
  if (!StringIsEmpty(buffer))
    canvas.DrawClippedText(left, top2, rc.right - leg_info_width - left,
                           buffer);

  // Draw turnpoint name
  canvas.Select(name_font);
  OrderedTaskPointLabel(tp.GetType(), tp.GetWaypoint().name.c_str(),
                        DrawListIndex, buffer);
  canvas.DrawClippedText(left, rc.top + Layout::FastScale(2),
                         rc.right - leg_info_width - left, buffer);
}