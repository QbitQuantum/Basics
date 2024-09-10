bool PosEditor::event(QEvent *e)
      {
      if (e->type() == QEvent::FocusIn || e->type() == QEvent::FocusOut) {
            repaint( rect(), false);
            }
      else if (e->type() == QEvent::ShortcutOverride) {
            QKeyEvent* ke = (QKeyEvent*) e;
            switch (ke->key()) {
                  case Qt::Key_Delete:
                  case Qt::Key_Backspace:
                  case Qt::Key_Up:
                  case Qt::Key_Down:
                  case Qt::Key_Left:
                  case Qt::Key_Right:
                        ke->accept();
                  default:
                        break;
                  }
            }
      return QWidget::event(e);
      }