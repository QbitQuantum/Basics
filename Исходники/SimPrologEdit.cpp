void SimPrologEdit::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {

    case Qt::Key_F1: {
        QTextCursor c = textCursor();
        c.select(c.WordUnderCursor);
        QString s = c.selectedText();
        if (s.length())
            for (QWidget *w = this; w; w = w->parentWidget())
                if (auto m = qobject_cast<spqrMainWindow*>(w)) {
                    m->activate(m->t_helpdoc);
                    m->helpDoc()->setUrl(
                        QString("http://localhost:%1/search?for=%2&in=all&match=summary")
                                .arg(m->DOC_PORT).arg(s));
                    break;
                }
    }   break;

    case Qt::Key_Tab:
        e->ignore();
        return;
    case Qt::Key_Backtab:
        e->ignore();
        return;
    }

    SimPrologEditBase::keyPressEvent(e);
}