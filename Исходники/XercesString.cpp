XercesString::XercesString(const wstring& in)
    : basic_string<XMLCh>()
{
    for(unsigned int i=0; i<in.length(); ++i) {
        wchar_t utf32 = in[i];
        if (utf32 >= 0x10000UL) {
            push_back(0xD800 - 0x40 + (utf32 >> 10));
            push_back(0xDC00 + (utf32 & 0x3FF));
        }
        else