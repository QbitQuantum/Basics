wxString IniParser::ReadLineFromBuffer(wxString& buffer)
{
    int len = buffer.Length();
    int i = 0;
    while (i < len && buffer.GetChar(i) != _T('\n'))
        ++i;
    wxString str = buffer.Left(i);
    while (i < len && (buffer.GetChar(i) == _T('\n') || buffer.GetChar(i) == _T('\r')))
        ++i;
    buffer.Remove(0, i);
    buffer.Trim();
    return str;
}