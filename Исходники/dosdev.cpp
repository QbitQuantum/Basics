bool StringIsDriveLetter(const std::wstring& in)
{
    if (in.length() != 2)  return false;
    if (! iswalpha(in[0])) return false;
    if (in[1] != L':')     return false;
    return true;
}