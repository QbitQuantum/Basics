// proxy auth header username extraction
int digestinstance::identify(Socket &peercon, Socket &proxycon, HTTPHeader &h, std::string &string)
{
    // don't match for non-digest auth types
    String t = h.getAuthType();
    t.toLower();
    if (t != "digest")
        return DGAUTH_NOMATCH;
    // extract username
    string = h.getRawAuthData();
    if (string.length() > 0) {
        String temp(string);
        temp = temp.after("username=\"");
        temp = temp.before("\"");
        string = temp;
        return DGAUTH_OK;
    }
    return DGAUTH_NOMATCH;
}