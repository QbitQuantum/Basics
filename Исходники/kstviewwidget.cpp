void KstViewWidget::leaveEvent(QEvent *e) {
  //kstdDebug() << "Leave event" << endl;
  QWidget::leaveEvent(e);
  if (_view->viewMode() != KstTopLevelView::DisplayMode) {
    if (_menu) {
      return;
    }
    if (!_view->tracking()) {
      //kstdDebug() << "Not tracking" << endl;
      _view->clearFocus();
    } else {
      //kstdDebug() << "Tracking" << endl;
      if (_view->trackingIsMove() && _dragEnabled) {
        QDragObject *d = dragObject();
        if (d) {
          // First cancel any operations
          _view->cancelMouseOperations();
          _view->paint(KstPainter::P_PAINT);
          d->drag();
        }
      }
    }
  }
}