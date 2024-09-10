QCString MIMECodec::decodeEndLine(const QCString &str)
{
  int size = str.length();
  const char *data = str.data();
  QCString buffer(size);
  char *buf = buffer.data();
  int index = 0;

  for (int i = 0; i < size; i++) {
    char c = data[i];

    if (c != '\r') {
      buf[index++] = c;
    }
  }

  buffer.truncate(index);
  return buffer;
}