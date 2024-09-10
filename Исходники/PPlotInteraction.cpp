bool PZoomInteraction::HandleKeyEvent (const PKeyEvent &inEvent) {

  if (inEvent.IsOnlyControlKeyDown () && inEvent.IsChar ()) {
    switch (inEvent.GetChar ()) {
    case 'r':
      mZoomMode = kZoom_Region;
      return true;
      break;
    case 'x':
      mZoomMode = kZoom_X;
      return true;
      break;
    case 'y':
      mZoomMode = kZoom_Y;
      return true;
      break;
    }
  }
  return false;
};