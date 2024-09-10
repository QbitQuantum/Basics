//===============================================================
bool MouseElementDeleter::eventFilter(QObject *widget, QEvent *e) {
  QMouseEvent *qMouseEv = (QMouseEvent *) e;

  if(qMouseEv != NULL) {
    node tmpNode;
    edge tmpEdge;
    ElementType type;
    GlMainWidget *glMainWidget = (GlMainWidget *) widget;

    if(e->type() == QEvent::MouseMove) {
      if (glMainWidget->doSelect(qMouseEv->x(), qMouseEv->y(), type, tmpNode, tmpEdge)) {
        glMainWidget->setCursor(QCursor(QPixmap(":/i_del.png")));
      }
      else {
        glMainWidget->setCursor(Qt::ArrowCursor);
      }

      return false;
    }
    else if (e->type() == QEvent::MouseButtonPress && qMouseEv->button()==Qt::LeftButton) {
      if (glMainWidget->doSelect(qMouseEv->x(), qMouseEv->y(), type, tmpNode, tmpEdge)) {
        Observable::holdObservers();
        Graph* graph = glMainWidget->getGraph();
        // allow to undo
        graph->push();

        switch(type) {
        case NODE:
          graph->delNode(tmpNode);
          break;

        case EDGE:
          graph->delEdge(tmpEdge);
          break;
        }

        glMainWidget->redraw();
        Observable::unholdObservers();
        return true;
      }
    }
  }

  return false;
}