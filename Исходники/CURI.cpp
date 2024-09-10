ECode CURI::ParseAuthority(
    /* [in] */ Boolean forceServer)
{
    if (mAuthority.IsNull()) {
        return NOERROR;
    }

    String tempUserInfo;
    String temp = mAuthority;
    Int32 index = temp.IndexOf('@');
    Int32 hostIndex = 0;
    if (index != -1) {
        // remove user info
        tempUserInfo = temp.Substring(0, index);
        FAIL_RETURN(ValidateUserInfo(mAuthority, tempUserInfo, 0));
        temp = temp.Substring(index + 1); // host[:port] is left
        hostIndex = index + 1;
    }

    index = temp.LastIndexOf(':');
    Int32 endIndex = temp.IndexOf(']');

    String tempHost;
    Int32 tempPort = -1;
    if (index != -1 && endIndex < index) {
        // determine port and host
        tempHost = temp.Substring(0, index);

        Char32 firstPortChar = temp.GetChar(index + 1);
        if (firstPortChar >= '0' && firstPortChar <= '9') {
            // allow only digits, no signs
            ECode ec = StringUtils::Parse(temp.Substring(index + 1), &tempPort);
            if (ec == (ECode)E_NUMBER_FORMAT_EXCEPTION) {
                if (forceServer) {
                    ALOGE("%s Invalid port number %d", mAuthority.string(), hostIndex + index + 1);
                    return E_URI_SYNTAX_EXCEPTION;
                }
                return NOERROR;
            }
        } else {
            if (forceServer) {
                ALOGE("%s Invalid port number %d", mAuthority.string(), hostIndex + index + 1);
                return E_URI_SYNTAX_EXCEPTION;
            }
            return NOERROR;
        }
    }
    else {
        tempHost = temp;
    }

    if (tempHost.IsEmpty()) {
        if (forceServer) {
            return E_URI_SYNTAX_EXCEPTION;
        }
        return NOERROR;
    }

    Boolean isValid = FALSE;
    FAIL_RETURN(IsValidHost(forceServer, tempHost, &isValid));
    if (!isValid) {
        return NOERROR;
    }

    // this is a server based uri,
    // fill in the userInfo, host and port fields
    mUserInfo = tempUserInfo;
    mHost = tempHost;
    mPort = tempPort;
    mServerAuthority = TRUE;

    return NOERROR;
}