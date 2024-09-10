 bool PropertyLineEdit::event(QEvent *e)
 {
     // handle 'Select all' here as it is not done in the QLineEdit
     if (e->type() == QEvent::ShortcutOverride && !isReadOnly()) {
         QKeyEvent* ke = static_cast<QKeyEvent*> (e);
         if (ke->modifiers() & Qt::ControlModifier) {
             if(ke->key() == Qt::Key_A) {
                 ke->accept();
                 return true;
             }
         }
     }
     return QLineEdit::event(e);
 }