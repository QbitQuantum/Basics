// Convert 2-digit hex number to decimal
int wxHexToDec(const wxString& str)
{
    char buf[2];
    buf[0] = str.GetChar(0);
    buf[1] = str.GetChar(1);
    return wxHexToDec((const char*) buf);
}