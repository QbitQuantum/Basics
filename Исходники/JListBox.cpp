void JListBox::beforePaint(JRect *rect) {
  if (!updateLock++) {
    if (focusOn && cursorVisible) {
      showCursor(rect);
      cursorVisible--;
    }
  }
}