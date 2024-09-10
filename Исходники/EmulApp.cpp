bool EmulApp::eventFilter(QObject *watched, QEvent *event)
{
    int type = static_cast<int>(event->type());
    if (type == QEvent::KeyPress) {
    } 
    MainWindow *mw = dynamic_cast<MainWindow *>(watched);
    if (mw) {
        if (type == LogLineEventType) {
            LogLineEvent *evt = dynamic_cast<LogLineEvent *>(event);
            if (evt && mw->textEdit()) {
                QTextEdit *te = mw->textEdit();
                QColor origcolor = te->textColor();
                te->setTextColor(evt->color);
                te->append(evt->str);

                // make sure the log textedit doesn't grow forever
                // so prune old lines when a threshold is hit
                nLinesInLog += evt->str.split("\n").size();
                if (nLinesInLog > nLinesInLogMax) {
                    const int n2del = MAX(nLinesInLogMax/10, nLinesInLog-nLinesInLogMax);
                    QTextCursor cursor = te->textCursor();
                    cursor.movePosition(QTextCursor::Start);
                    for (int i = 0; i < n2del; ++i) {
                        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor);
                    }
                    cursor.removeSelectedText(); // deletes the lines, leaves a blank line
                    nLinesInLog -= n2del;
                }

                te->setTextColor(origcolor);
                te->moveCursor(QTextCursor::End);
                te->ensureCursorVisible();
                return true;
            } else {
                return false;
            }
        } else if (type == StatusMsgEventType) {
            StatusMsgEvent *evt = dynamic_cast<StatusMsgEvent *>(event);
            if (evt && mw->statusBar()) {
                mw->statusBar()->showMessage(evt->msg, evt->timeout);
                return true;
            } else {
                return false;
            }
        }
    }
    if (watched == this) {
        if (type == QuitEventType) {
            quit();
            return true;
        }
        if (type == SoundTrigEventType) {
            SoundTrigEvent *evt = dynamic_cast<SoundTrigEvent *>(event);
            if (evt) trigSound(evt->trig);
            if (evt->listener) evt->listener->triggered(evt->trig);
            return true;
        }
        if (type == SoundEventType) {
            SoundEvent *evt = dynamic_cast<SoundEvent *>(event);
            if (evt) gotSound(evt->id, evt->name, evt->loops);
            if (evt->listener) evt->listener->gotSound(evt->id);
            return true;
        }
    }
    // otherwise do default action for event which probably means
    // propagate it down
    return QApplication::eventFilter(watched, event);
}