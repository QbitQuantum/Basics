void KTextEditingPlugin::selectWord(QTextCursor &cursor, int cursorPosition) const
{
    cursor.setPosition(cursorPosition);
    QTextBlock block = cursor.block();
    cursor.setPosition(block.position());
    cursorPosition -= block.position();
    QString string = block.text();
    int pos = 0;
    bool space = false;
    QString::Iterator iter = string.begin();
    while (iter != string.end()) {
        if (iter->isSpace()) {
            if (space) ;// double spaces belong to the previous word
            else if (pos < cursorPosition)
                cursor.setPosition(pos + block.position() + 1); // +1 because we don't want to set it on the space itself
            else
                space = true;
        } else if (space)
            break;
        pos++;
        iter++;
    }
    cursor.setPosition(pos + block.position(), QTextCursor::KeepAnchor);
}