void ExpressTextEdit::mouseMoveEvent(QMouseEvent *e)
{
    QTextCursor cursor = cursorForPosition(e->pos());
    cursor.select(QTextCursor::WordUnderCursor);
    QString wordUnderCursor = cursor.selectedText();

    const EntityDescriptor * entityDescriptor = m_Registry->FindEntity(wordUnderCursor.toAscii());
    const TypeDescriptor * typeDescriptor = m_Registry->FindType(wordUnderCursor.toAscii());
    if (entityDescriptor )
    {
        std::string str;
        setToolTip(entityDescriptor->GenerateExpress(str));
        if (QApplication::overrideCursor()==0)
            QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(typeDescriptor)
    {
        std::string str;
        setToolTip(typeDescriptor->GenerateExpress(str));
        if (QApplication::overrideCursor()==0)
            QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
        setToolTip(QString());
        QApplication::restoreOverrideCursor();
    }
}