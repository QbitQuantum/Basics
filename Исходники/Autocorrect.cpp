void Autocorrect::fixTwoUppercaseChars()
{
    if (! m_fixTwoUppercaseChars) return;
    if (m_word.length() <= 2) return;

    if (m_twoUpperLetterExceptions.contains(m_word.trimmed()))
        return;

    QChar firstChar = m_word.at(0);
    QChar secondChar = m_word.at(1);

    if (secondChar.isUpper()) {
        QChar thirdChar = m_word.at(2);

        if (firstChar.isUpper() && thirdChar.isLower())
            m_word.replace(1, 1, secondChar.toLower());
    }
}