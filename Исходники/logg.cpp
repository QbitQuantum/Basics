    // if necessary truncates the given string and adds an ellipsis
    wxString EllipsizeString(const wxString &text)
    {
        if (ms_maxLength > 0 &&
                text.length() > ms_maxLength)
        {
            wxString ret(text);
            ret.Truncate(ms_maxLength);
            ret << "...";
            return ret;
        }

        return text;
    }