void RenderCombineText::getStringToRender(int start, StringView& string, int& length) const
{
    ASSERT(start >= 0);
    if (m_isCombined) {
        string = StringView(originalText());
        length = string.length();
        return;
    }

    string = text().createView(start, length);
}