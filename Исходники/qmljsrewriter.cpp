bool Rewriter::includeSurroundingWhitespace(int &start, int &end) const
{
    bool includeStartingWhitespace = true;
    bool paragraphFound = false;

    if (end >= 0) {
        QChar c = m_originalText.at(end);
        while (c.isSpace()) {
            ++end;

            if (c == QChar::ParagraphSeparator) {
                paragraphFound = true;
                break;
            } else if (end == m_originalText.length()) {
                break;
            }

            c = m_originalText.at(end);
        }

        includeStartingWhitespace = paragraphFound;
    }

    if (includeStartingWhitespace) {
        while (start > 0) {
            const QChar c = m_originalText.at(start - 1);

            if (!c.isSpace())
                break;
            else if (c == QChar::ParagraphSeparator)
                break;

            --start;
        }
    }

    return paragraphFound;
}