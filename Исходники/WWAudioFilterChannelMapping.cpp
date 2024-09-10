static bool
ParseChannelMappingItem(std::wstring s, ChannelMappingItem &item_return)
{
    std::wstring::size_type found = s.find(L'>');
    if (found == std::wstring::npos || s.length()-1 <= found) {
        return false;
    }

    s[found] = 0;
    const wchar_t *sc = s.c_str();

    swscanf_s(&sc[0],       L"%u", &item_return.fromCh);
    swscanf_s(&sc[found+1], L"%u", &item_return.toCh);

    return true;
}