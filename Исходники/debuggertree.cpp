int DebuggerTree::FindCommaPos(const wxString& str)
{
    // comma is a special case because it separates the fields
    // but it can also appear in a function/template signature, where
    // we shouldn't treat it as a field separator

    // what we 'll do now, is decide if the comma is inside
    // a function signature.
    // we 'll do it by counting the opening and closing parenthesis/angled-brackets
    // *up to* the comma.
    // if they 're equal, it's a field separator.
    // if they 're not, it's in a function signature
    // ;)

    int len = str.Length();
    int i = 0;
    int parCount = 0;
    int braCount = 0;
    bool inQuotes = false;
    while (i < len)
    {
        wxChar ch = str.GetChar(i);
        switch (ch)
        {
            case _T('('):
                ++parCount; // increment on opening parenthesis
                break;

            case _T(')'):
                --parCount; // decrement on closing parenthesis
                break;

            case _T('<'):
                ++braCount; // increment on opening angle bracket
                break;

            case _T('>'):
                --braCount; // decrement on closing angle bracket
                break;

            case _T('"'):
                // fall through
            case _T('\''):
                inQuotes = !inQuotes; // toggle inQuotes flag
                break;

            default:
                break;
        }

        // if it's not inside quotes *and* we have parCount == 0, it's a field separator
        if (!inQuotes && parCount == 0 && braCount == 0 && ch == _T(','))
            return i;
        ++i;
    }
    return -1;
}