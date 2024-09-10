    bool FastoEditor::eventFilter(QObject* object, QEvent* event)
    {
        if (object == scin_) {
            if (event->type() == QEvent::KeyPress) {
                QKeyEvent *keyEvent = (QKeyEvent *)event;
                if (((keyEvent->modifiers() & Qt::ControlModifier) && keyEvent->key() == Qt::Key_F)) {
                    findPanel_->show();
                    findLine_->setFocus();
                    //findPanel_->selectAll();
                    keyEvent->accept();
                    return true;
                }
            }
        }

        return QWidget::eventFilter(object, event);
    }