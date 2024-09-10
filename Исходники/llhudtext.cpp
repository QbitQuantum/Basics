void LLHUDText::addLine(const std::string &text_utf8,
                        const LLColor4& color,
                        const LLFontGL::StyleFlags style,
                        const LLFontGL* font)
{
    LLWString wline = utf8str_to_wstring(text_utf8);
    if (!wline.empty())
    {
        // use default font for segment if custom font not specified
        if (!font)
        {
            font = mFontp;
        }
        typedef boost::tokenizer<boost::char_separator<llwchar>, LLWString::const_iterator, LLWString > tokenizer;
        LLWString seps(utf8str_to_wstring("\r\n"));
        boost::char_separator<llwchar> sep(seps.c_str());

        tokenizer tokens(wline, sep);
        tokenizer::iterator iter = tokens.begin();

        while (iter != tokens.end())
        {
            U32 line_length = 0;
            do
            {
                F32 max_pixels = HUD_TEXT_MAX_WIDTH_NO_BUBBLE;
                S32 segment_length = font->maxDrawableChars(iter->substr(line_length).c_str(), max_pixels, wline.length(), LLFontGL::WORD_BOUNDARY_IF_POSSIBLE);
                LLHUDTextSegment segment(iter->substr(line_length, segment_length), style, color, font);
                mTextSegments.push_back(segment);
                line_length += segment_length;
            }
            while (line_length != iter->size());
            ++iter;
        }
    }
}