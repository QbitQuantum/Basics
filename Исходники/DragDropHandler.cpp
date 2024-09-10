void
DragDropHandlerP::dropEvent(QDropEvent * event)
{
  const QMimeData * mimedata = event->mimeData();

  SoSeparator * root;
  SoInput in;
  QByteArray bytes;

  if (mimedata->hasUrls()) {
    QUrl url = mimedata->urls().takeFirst();
    if (url.scheme().isEmpty() || url.scheme().toLower() == QString("file") ) {
      // attempt to open file
      if (!in.openFile(url.toLocalFile().toLatin1().constData())) return;
    }
  } else if (mimedata->hasText()) {
    /* FIXME 2007-11-09 preng: dropping text buffer does not work on Windows Vista. */
    bytes = mimedata->text().toUtf8();
    in.setBuffer((void *) bytes.constData(), bytes.size());
    if (!in.isValidBuffer()) return;
  }

  // attempt to import it
  root = SoDB::readAll(&in);
  if (root == NULL) return;

  // set new scenegraph
  this->quarterwidget->setSceneGraph(root);
  this->quarterwidget->viewport()->update();
}