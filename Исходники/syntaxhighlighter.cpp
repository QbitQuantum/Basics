void SyntaxHighlighter::Highlight(const std::wstring& s, SyntaxHighlighter::CallbackType highlight)
{
    if (s.empty())
        return;

    const int length = int(s.length());

    for (auto i = s.begin(); i != s.end(); ++i)
    {
        if (!u_isblank(*i))
        {
            int wlen = int(i - s.begin());
            if (wlen)
                highlight(0, wlen, LeadingWhitespace);
            break;
        }
    }

    for (auto i = s.rbegin(); i != s.rend(); ++i)
    {
        if (!u_isblank(*i))
        {
            int wlen = int(i - s.rbegin());
            if (wlen)
                highlight(length - wlen, length, LeadingWhitespace);
            break;
        }
    }

    for (auto i = s.begin(); i != s.end(); ++i)
    {
        if (*i == '\\')
        {
            int pos = int(i - s.begin());
            if (++i == s.end())
                break;
            // TODO: highlight full syntax, incl. octals: http://en.cppreference.com/w/cpp/language/escape
            switch (*i)
            {
                case '0':
                case 'n':
                case 'r':
                case 't':
                case '"':
                case '\\':
                    highlight(pos, pos + 2, Escape);
                    break;
                default:
                    break;
            }
        }
    }
}