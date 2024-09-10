ScrollbarPart ScrollbarTheme::hitTest(const ScrollbarThemeClient& scrollbar,
                                      const IntPoint& positionInRootFrame) {
  ScrollbarPart result = NoPart;
  if (!scrollbar.enabled())
    return result;

  IntPoint testPosition = scrollbar.convertFromRootFrame(positionInRootFrame);
  testPosition.move(scrollbar.x(), scrollbar.y());

  if (!scrollbar.frameRect().contains(testPosition))
    return NoPart;

  result = ScrollbarBGPart;

  IntRect track = trackRect(scrollbar);
  if (track.contains(testPosition)) {
    IntRect beforeThumbRect;
    IntRect thumbRect;
    IntRect afterThumbRect;
    splitTrack(scrollbar, track, beforeThumbRect, thumbRect, afterThumbRect);
    if (thumbRect.contains(testPosition))
      result = ThumbPart;
    else if (beforeThumbRect.contains(testPosition))
      result = BackTrackPart;
    else if (afterThumbRect.contains(testPosition))
      result = ForwardTrackPart;
    else
      result = TrackBGPart;
  } else if (backButtonRect(scrollbar, BackButtonStartPart)
                 .contains(testPosition)) {
    result = BackButtonStartPart;
  } else if (backButtonRect(scrollbar, BackButtonEndPart)
                 .contains(testPosition)) {
    result = BackButtonEndPart;
  } else if (forwardButtonRect(scrollbar, ForwardButtonStartPart)
                 .contains(testPosition)) {
    result = ForwardButtonStartPart;
  } else if (forwardButtonRect(scrollbar, ForwardButtonEndPart)
                 .contains(testPosition)) {
    result = ForwardButtonEndPart;
  }
  return result;
}