/**
 * Prepares the display for the next message
 * @param msgType :: One of the predefined message types
 */
void ScriptOutputDisplay::prepareForNewMessage(const MessageType msgType) {
  // Ensure the cursor is in the correct position. This affects the font
  // unfortunately
  moveCursor(QTextCursor::End);
  resetFont();
  // zoom(0);
  if (msgType == ScriptOutputDisplay::Error) {
    setTextColor(Qt::red);
  } else {
    setTextColor(Qt::black);
  }
}