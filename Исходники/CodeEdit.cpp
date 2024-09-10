bool CodeEdit::Untabify(wxString& text) const
{

    // wxString::Replace is very slow with a big string because the operation
    // is performed in place (which requires a lot of copying). Instead we use
    // a different method with a second string.

    assert(m_indentationSize < 32);

    char indentation[32];
    memset(indentation, ' ', 32);
    indentation[m_indentationSize] = 0;

    wxString result;
    result.reserve(text.Length());

    unsigned int numTabs = 0;

    for (unsigned int i = 0; i < text.Length(); ++i)
    {

        if (text[i] == '\t')
        {
            result += indentation;
            ++numTabs;
        }
        else
        {
            result += text[i];
        }

    }

    if (numTabs > 0)
    {
        text = result;
        return true;
    }
    return false;

}