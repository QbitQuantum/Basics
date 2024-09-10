void Mac::OSXStyle::removeWindow(QWidget *w) {
    if (w && windowMenu && actions.contains(w)) {
        QAction *act=actions.take(w);
        windowMenu->removeAction(act);
        disconnect(act, SIGNAL(triggered()), this, SLOT(showWindow()));
        disconnect(w, SIGNAL(windowTitleChanged(QString)), this, SLOT(windowTitleChanged()));
        act->deleteLater();
    }
}