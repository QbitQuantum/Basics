wxString IACFile::ReadToken(wxInputStream &file) {
    // 0 = read chars until digit
    // 1 = read digits until no digit
    // 2 = token found
    wxString token = wxEmptyString;

    int mode = 0;

    while (file.IsOk() && mode != 2) {
        int c = file.GetC();

        if (c != wxEOF && c <= 128) {
            if (c == '\n' && m_tokensI > 0) {
                m_newlineTokens.push_back(m_tokensI + 1);
            }
            m_RawData.Append((char)c);
            switch (mode) {
                case 0:
                    if (isdigit(c)) {
                        token.Append((char)c);
                        mode = 1;
                    }
                    break;
                case 1:
                    if (isdigit(c) || c == '/') {
                        token.Append((char)c);
                    } else {
                        if (token.Len() == 5) {
                            // token found!!
                            mode = 2;
                        } else {
                            token.Empty();
                        }
                    }
                    break;
                    /* this is dead code
                                case 2:
                                    mode = 0;
                                    break;
                    */
            }  // case
        }
    }  // while
    if (mode != 2) {
        token.Empty();
    }

    return token;
}