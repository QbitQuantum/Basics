bool QIODeviceProto::putChar(char c)
{
  QIODevice *item = qscriptvalue_cast<QIODevice*>(thisObject());
  if (item)
    return item->putChar(c);
  return false;
}