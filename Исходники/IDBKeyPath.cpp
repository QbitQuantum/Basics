IDBKeyPathLexer::TokenType IDBKeyPathLexer::lexIdentifier(String& element)
{
    StringView start = m_remainingText;
    if (!m_remainingText.isEmpty() && isIdentifierStartCharacter(m_remainingText[0]))
        m_remainingText = m_remainingText.substring(1);
    else
        return TokenError;

    while (!m_remainingText.isEmpty() && isIdentifierCharacter(m_remainingText[0]))
        m_remainingText = m_remainingText.substring(1);

    element = start.substring(0, start.length() - m_remainingText.length()).toString();
    return TokenIdentifier;
}