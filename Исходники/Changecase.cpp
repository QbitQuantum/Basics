void Changecase::toggleCase()
{
    QTextBlock block = m_document->findBlock(m_startPosition);
    int pos = block.position();
    bool finished = false;

    while (true) {
        QString text = block.text();
        QString result;

        QString::ConstIterator constIter = text.constBegin();
        while (pos < m_endPosition && constIter != text.constEnd()) {
            if (pos >= m_startPosition) {
                if (constIter->isLower())
                    result.append(constIter->toUpper());
                else if (constIter->isUpper())
                    result.append(constIter->toLower());
                else
                    result.append(*constIter);
            }

            pos++;
            constIter++;
        }

        if (!(block.isValid() && block.position() + block.length() < m_endPosition))
            finished = true;

        if (result != text) {
            m_cursor.setPosition(qMax(m_startPosition, block.position()));
            m_cursor.setPosition(qMin(pos, m_endPosition), QTextCursor::KeepAnchor);
            m_cursor.insertText(result);
        }

        if (finished)
            break;

        block = block.next();
        pos = block.position();
    }
}