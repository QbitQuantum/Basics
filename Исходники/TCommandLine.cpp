void TCommandLine::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        QTextCursor c = cursorForPosition(event->pos());
        c.select(QTextCursor::WordUnderCursor);

        if (!Hunspell_spell(mpHunspell, c.selectedText().toLatin1().data())) {
            char** sl;
            mHunspellSuggestionNumber = Hunspell_suggest(mpHunspell, &sl, c.selectedText().toLatin1().data());
            auto popup = new QMenu(this);
            for (int i = 0; i < mHunspellSuggestionNumber; i++) {
                QAction* pA;
                pA = popup->addAction(sl[i]);
                connect(pA, &QAction::triggered, this, &TCommandLine::slot_popupMenu);
            }
            mpHunspellSuggestionList = sl;
            mPopupPosition = event->pos();
            popup->popup(event->globalPos());
        }

        event->accept();
        return;
    }
    QPlainTextEdit::mousePressEvent(event);
}