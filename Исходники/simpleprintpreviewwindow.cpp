bool KGVSimplePrintPreviewWindow::event( QEvent * e )
{
  QEvent::Type t = e->type();
  if (t==QEvent::KeyPress)
  {
    QKeyEvent *ke = static_cast<QKeyEvent*>(e);
    const int k = ke->key();
    bool ok = true;
    if (k==Qt::Key_Equal || k==Qt::Key_Plus)
            slotZoomInClicked();
    else if (k==Qt::Key_Minus)
            slotZoomOutClicked();
    else if (k==Qt::Key_Home)
            slotFirstClicked();
    else if (k==Qt::Key_End)
            slotLastClicked();
    else
            ok = false;

    if (ok)
    {
      ke->accept();
      return true;
    }
  }
  else if (t==QEvent::ShortcutOverride)
  {
    QKeyEvent *ke = static_cast<QKeyEvent*>(e);
    const int k = ke->key();
    bool ok = true;
    if (k==Qt::Key_PageUp)
            slotPreviousClicked();
    else if (k==Qt::Key_PageDown)
            slotNextClicked();
    else
            ok = false;

    if (ok) {
            ke->accept();
            return true;
    }
  }
  return QWidget::event(e);
}