inline int DetectRepeatingSymbols(wxString const &str, int pos)
{
    int newPos = -1, currPos = pos;
    while (1)
    {
        if (currPos + 4 >= static_cast<int>(str.length()))
            break;
        if (str[currPos + 1] != wxT(','))
            break;
        if (str[currPos + 3] == wxT('\''))
        {
            const wxString &s = str.substr(currPos + 3, str.length() - (currPos + 3));
            if (regexRepeatedChars.Matches(s))
            {
                size_t start, length;
                regexRepeatedChars.GetMatch(&start, &length, 0);
                newPos = currPos + 3 + length;
                if ((newPos + 4 < static_cast<int>(str.length()))
                    && str[newPos] == wxT(',') && str[newPos + 2] == wxT('"'))
                {
                    newPos += 3;
                    while (newPos < static_cast<int>(str.length()) && str[newPos] != wxT('"'))
                        ++newPos;
                    if (newPos + 1 < static_cast<int>(str.length()) && str[newPos] == wxT('"'))
                        ++newPos;
                }
                currPos = newPos;
            }
            else
                break;
        }
        else
            break;

        // move the current position to point at the '"' character
        currPos--;
    }
    return newPos;
}