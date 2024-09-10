void QtTrackerMoveListener::Moved(QtTracker* tracker, const QPoint& location)
{
  // Select a drop target; use the global one by default
  IDropTarget::Pointer target;

  QWidget* targetControl = Tweaklets::Get(GuiWidgetsTweaklet::KEY)->GetCursorControl();

  // Get the drop target for this location
  target = DragUtil::GetDropTarget(targetControl, draggedItem, location,
      tracker->GetRectangle());

  // Set up the tracker feedback based on the target
  QRect snapTarget;
  if (target != 0)
  {
    snapTarget = target->GetSnapRectangle();

    tracker->SetCursor(target->GetCursor());
  }
  else
  {
    tracker->SetCursor(CURSOR_INVALID);
  }

  // If snapping then reset the tracker's rectangle based on the current drop target
  if (allowSnapping)
  {
    if (snapTarget.width() < 0 || snapTarget.height() < 0)
    {
      snapTarget = QRect(sourceBounds.x() + location.x() - initialLocation.x(),
          sourceBounds.y() + location.y() - initialLocation.y(), sourceBounds.width(),
          sourceBounds.height());
    }

    // Try to prevent flicker: don't change the rectangles if they're already in
    // the right location
    QRect currentRectangle = tracker->GetRectangle();

    if (!(currentRectangle == snapTarget))
    {
      tracker->SetRectangle(snapTarget);
    }
  }

}