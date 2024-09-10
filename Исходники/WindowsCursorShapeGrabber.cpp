HCURSOR WindowsCursorShapeGrabber::getHCursor()
{
  CURSORINFO cursorInfo;
  cursorInfo.cbSize = sizeof(CURSORINFO);

  if (GetCursorInfo(&cursorInfo) == 0) {
    return false;
  }

  return cursorInfo.hCursor;
}