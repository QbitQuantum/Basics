bool wxSimpleHtmlParser::IsWord()
{
    return (IsAlpha(GetChar(m_pos)));
}