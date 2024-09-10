std::string WideToNarrow(const std::wstring& ws)
{
    const std::locale locale(""); // WARNING: This only needs to be done one time.
    typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
    const converter_type& converter = std::use_facet<converter_type>(locale);
    std::vector<char> to(ws.length() * converter.max_length());
    std::mbstate_t state;
    const wchar_t* from_next;
    char* to_next;
    const converter_type::result result = converter.out(state, ws.data(), ws.data() + ws.length(), from_next, &to[0], &to[0] + to.size(), to_next);
    if (result == converter_type::ok || result == converter_type::noconv)
    {
        const std::string s(&to[0], to_next);
        return s;
    }
    return "";
}