int JavascriptInvocation::keyCodeFor(const QChar &key) {
  switch(key.unicode()) {
    case 0x18:
      return Qt::Key_Cancel;
    case 0x08:
      return Qt::Key_Backspace;
    case 0x09:
      return Qt::Key_Tab;
    case 0x0A:
      return Qt::Key_Return;
    case 0x1B:
      return Qt::Key_Escape;
    case 0x7F:
      return Qt::Key_Delete;
    default:
      int keyCode = key.toUpper().toLatin1();
      if (keyCode >= Qt::Key_Space || keyCode <= Qt::Key_AsciiTilde)
        return keyCode;
      else
        return Qt::Key_unknown;
  }
}