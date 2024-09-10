/*!
  Makes the ScreenBoard catch all mouse events (effectively preventing other
  windows or applications
  to get them), and delivers them to drawings. An appropriate cursor should be
  specified to inform the
  user that tout-court mouse grabbing takes place.
*/
void ScreenBoard::grabMouse(const QCursor &cursor) {
  m_grabbing = true;
  m_cursor   = cursor;

  // Place a mouse-tracking dummy drawing among drawings
  m_drawings.push_back(&::tracker);

  // Make all screen widgets react to mouse events, and show them
  int i, size = m_screenWidgets.size();
  for (i = 0; i < size; ++i) {
    QWidget *screenWidget = m_screenWidgets[i];
    if (screenWidget) {
      screenWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
      screenWidget->setCursor(m_cursor);
    }
  }
}