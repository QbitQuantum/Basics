QVariant QTextEditProto::loadResource(int type, const QUrl &name)
{
  QTextEdit *item = qscriptvalue_cast<QTextEdit*>(thisObject());
  if (item)
    return item->loadResource(type, name);
  return QVariant();
}