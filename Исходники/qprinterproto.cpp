bool QPrinterProto::abort()
{
  QPrinter *item = qscriptvalue_cast<QPrinter*>(thisObject());
  if (item)
    return item->abort();
  return false;
}