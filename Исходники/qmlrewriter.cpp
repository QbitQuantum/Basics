// FIXME: duplicate code in the QmlJS::Rewriter class, remove this
bool QMLRewriter::includeSurroundingWhitespace(int &start, int &end) const
{
    QTextDocument *doc = m_textModifier->textDocument();
    bool includeStartingWhitespace = true;
    bool paragraphFound = false;

    if (end >= 0) {
        QChar c = doc->characterAt(end);
        while (c.isSpace()) {
            ++end;

            if (c == QChar::ParagraphSeparator) {
                paragraphFound = true;
                break;
            } else if (end == doc->characterCount()) {
                break;
            }

            c = doc->characterAt(end);
        }

        includeStartingWhitespace = paragraphFound;
    }

    if (includeStartingWhitespace) {
        while (start > 0) {
            const QChar c = doc->characterAt(start - 1);

            if (!c.isSpace())
                break;
            else if (c == QChar::ParagraphSeparator)
                break;

            --start;
        }
    }

    return paragraphFound;
}