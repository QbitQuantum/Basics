inline std::wstring search_path(const std::wstring &filename,
    std::wstring path = L"")
{
    if (path.empty())
    {
        path = ::_wgetenv(L"PATH");
        if (path.empty())
            BOOST_PROCESS_THROW(std::runtime_error(
                "Environment variable PATH not found"));
    }

    typedef boost::tokenizer<boost::char_separator<wchar_t>,
        std::wstring::const_iterator, std::wstring> tokenizer;
    boost::char_separator<wchar_t> sep(L";");
    tokenizer tok(path, sep);
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    {
        boost::filesystem::path p = *it;
        p /= filename;
        boost::array<std::wstring, 4> extensions =
            { L"", L".exe", L".com", L".bat" };
        for (boost::array<std::wstring, 4>::iterator it2 = extensions.begin();
            it2 != extensions.end(); ++it2)
        {
            boost::filesystem::path p2 = p;
            p2 += *it2;
            boost::system::error_code ec;
            bool file = boost::filesystem::is_regular_file(p2, ec);
            if (!ec && file &&
                SHGetFileInfoW(p2.c_str(), 0, 0, 0, SHGFI_EXETYPE))
            {
                return p2.wstring();
            }
        }
    }
    return L"";
}