IDropTarget::Pointer DragUtil::DragToTarget(Object::Pointer draggedItem,
    const Rectangle& sourceBounds, const Point& initialLocation,
    bool allowSnapping)
{
  //final Display display = Display.getCurrent();

  // Testing...immediately 'drop' onto the test target
  if (forcedDropTarget != 0)
  {
    Point location = forcedDropTarget->GetLocation();

    void* currentControl =
        Tweaklets::Get(GuiWidgetsTweaklet::KEY)->FindControl(
            forcedDropTarget->GetShells(), location);
    return GetDropTarget(currentControl, draggedItem, location, sourceBounds);
  }

  // Create a tracker.  This is just an XOR rect on the screen.
  // As it moves we notify the drag listeners.
  ITracker* tracker = Tweaklets::Get(DnDTweaklet::KEY)->CreateTracker();
  //tracker.setStippled(true);

  GuiTk::IControlListener::Pointer trackerListener(new TrackerMoveListener(
      draggedItem, sourceBounds, initialLocation, allowSnapping));

  tracker->AddControlListener(trackerListener);

  // Setup...when the drag starts we might already be over a valid target, check this...
  // If there is a 'global' target then skip the check
  IDropTarget::Pointer target;
  void* startControl =
      Tweaklets::Get(GuiWidgetsTweaklet::KEY)->GetCursorControl();

  if (startControl != 0 && allowSnapping)
  {
    target = GetDropTarget(startControl, draggedItem, initialLocation,
        sourceBounds);
  }

  // Set up an initial tracker rectangle
  Rectangle startRect = sourceBounds;
  if (target != 0)
  {
    Rectangle rect = target->GetSnapRectangle();

    if (rect.width != 0 && rect.height != 0)
    {
      startRect = rect;
    }

    tracker->SetCursor(target->GetCursor());
  }

  if (startRect.width != 0 && startRect.height != 0)
  {
    tracker->SetRectangle(startRect);
  }

  // Tracking Loop...tracking is preformed on the 'SWT.Move' listener registered
  // against the tracker.

  //  // HACK:
  //  // Some control needs to capture the mouse during the drag or other
  //  // controls will interfere with the cursor
  //  Shell shell = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getShell();
  //  if (shell != null)
  //  {
  //    shell.setCapture(true);
  //  }

  // Run tracker until mouse up occurs or escape key pressed.
  bool trackingOk = tracker->Open();

  //  // HACK:
  //  // Release the mouse now
  //  if (shell != null)
  //  {
  //    shell.setCapture(false);
  //  }

  // Done tracking...

  // Get the current drop target
  IDropTarget::Pointer dropTarget;
  Point finalLocation =
      Tweaklets::Get(GuiWidgetsTweaklet::KEY)->GetCursorLocation();
  void* targetControl =
      Tweaklets::Get(GuiWidgetsTweaklet::KEY)->GetCursorControl();
  dropTarget = GetDropTarget(targetControl, draggedItem, finalLocation,
      tracker->GetRectangle());

  // Cleanup...
  delete tracker;

  // if we're going to perform a 'drop' then delay the issuing of the 'finished'
  // callback until after it's done...
  if (trackingOk)
  {
    return dropTarget;
  }
  else if (dropTarget != 0)
  {
    // If the target can handle a 'finished' notification then send one
    dropTarget->DragFinished(false);
  }

  return IDropTarget::Pointer(0);
}