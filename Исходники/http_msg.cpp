void parse_headers_string(_Inout_z_ utf16char* headersStr, http_headers& headers)
{
    utf16char* context = nullptr;
    utf16char* line = wcstok_s(headersStr, CRLF, &context);
    while (line != nullptr)
    {
        const utility::string_t header_line(line);
        const size_t colonIndex = header_line.find_first_of(_XPLATSTR(":"));
        if (colonIndex != utility::string_t::npos)
        {
            utility::string_t key = header_line.substr(0, colonIndex);
            utility::string_t value = header_line.substr(colonIndex + 1, header_line.length() - colonIndex - 1);
            http::details::trim_whitespace(key);
            http::details::trim_whitespace(value);
            headers.add(key, value);
        }
        line = wcstok_s(nullptr, CRLF, &context);
    }
}