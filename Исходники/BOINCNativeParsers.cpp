// we got an unrecognized line.
// If it has two <'s (e.g. <foo>xx</foo>) return 0.
// If it's of the form <foo/> return 0.
// If it's of the form <foo> then scan for </foo> and return 0.
// Otherwise return ERR_XML_PARSE
//
int skip_unrecognized(wxChar* buf, MIOFILE& fin) {
    wxChar* p, *q, buf2[256];
    std::wstring close_tag;

    p = _tcschr(buf, wxT('<'));
    if (!p) {
        return -112;
    }
    if (_tcschr(p+1, wxT('<'))) {
        return 0;
    }
    q = _tcschr(p+1, wxT('>'));
    if (!q) {
        return -112;
    }
    if (q[-1] == '/') return 0;
    *q = 0;
    close_tag = std::wstring(wxT("</")) + std::wstring(p+1) + std::wstring(wxT(">"));
    while (fin.fgets(buf2, 256)) {
        if (_tcsstr(buf2, close_tag.c_str())) {
            return 0;
        }
    }
    return -112;
}