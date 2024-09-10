void SDLGraphicsSystem::executeGraphicsSystem(RLMachine& machine) {
  // For now, nothing, but later, we need to put all code each cycle
  // here.
  if (isResponsibleForUpdate() && screenNeedsRefresh()) {
    refresh(NULL);
    screenRefreshed();
    redraw_last_frame_ = false;
  } else if (isResponsibleForUpdate() && redraw_last_frame_) {
    redrawLastFrame();
    redraw_last_frame_ = false;
  }

  // Check to see if any of the graphics objects are reporting that
  // they want to force a redraw
  for_each(foregroundObjects().allocated_begin(),
           foregroundObjects().allocated_end(),
           bind(&GraphicsObject::execute, _1));

  // Update the seen.
  int current_time = machine.system().event().getTicks();
  if ((current_time - time_of_last_titlebar_update_) > 60) {
    time_of_last_titlebar_update_ = current_time;

    if (machine.sceneNumber() != last_seen_number_ ||
       machine.lineNumber() != last_line_number_) {
      last_seen_number_ = machine.sceneNumber();
      last_line_number_ = machine.lineNumber();
      setWindowTitle();
    }
  }

  GraphicsSystem::executeGraphicsSystem(machine);
}