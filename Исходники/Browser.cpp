//
// Detect a cookie in Internet Explorer by using the InternetGetCookie API.
// Supports: 3.x, 4.x, 5.x, 6.x, 7.x (UAC Turned Off), 8.x (UAC Turned Off), 9.x (UAC Turned Off), and 
// 10.x (UAC Turned Off).
//
bool detect_cookie_ie_supported(std::string& project_url, std::string& name, std::string& value)
{
    bool        bReturnValue = false;
    bool        bCheckDomainName = false;
    char        szCookieBuffer[4096];
    char*       pszCookieFragment = NULL;
    DWORD       dwSize = sizeof(szCookieBuffer)/sizeof(char);
    std::string strCookieFragment;
    std::string strCookieName;
    std::string strCookieValue;
    std::string hostname;
    std::string domainname;
    size_t      uiDelimeterLocation;


    // if we don't find the cookie at the exact project dns name, check one higher
    //   (i.e. www.worldcommunitygrid.org becomes worldcommunitygrid.org
    parse_hostname_ie_compatible(project_url, hostname, domainname);

    // InternetGetCookie expects them in URL format
    hostname = std::string("http://") + hostname + std::string("/");
    domainname = std::string("http://") + domainname + std::string("/");

    // First check to see if the desired cookie is assigned to the hostname.
    bReturnValue = InternetGetCookieA(hostname.c_str(), NULL, szCookieBuffer, &dwSize) == TRUE;
    if (!bReturnValue || (!strstr(szCookieBuffer, name.c_str()))) {
        bCheckDomainName = true;
    }

    // Next check if it was assigned to the domainname.
    if (bCheckDomainName) {
        bReturnValue = InternetGetCookieA(domainname.c_str(), NULL, szCookieBuffer, &dwSize) == TRUE;
        if (!bReturnValue || (!strstr(szCookieBuffer, name.c_str()))) {
            return false;
        }
    }

    // Format of cookie buffer:
    // 'cookie1=value1; cookie2=value2; cookie3=value3;
    //
    pszCookieFragment = strtok(szCookieBuffer, "; ");
    while(pszCookieFragment) {
        // Convert to a std::string so we can go to town
        strCookieFragment = pszCookieFragment;

        // Extract the name & value
        uiDelimeterLocation = strCookieFragment.find("=", 0);
        strCookieName = strCookieFragment.substr(0, uiDelimeterLocation);
        strCookieValue = strCookieFragment.substr(uiDelimeterLocation + 1);

        if (0 == strcmp(name.c_str(), strCookieName.c_str())) {
            // Now we found it!  Yea - auto attach!
            value = strCookieValue;
            bReturnValue = true;
        }

        pszCookieFragment = strtok(NULL, "; ");
    }

    return bReturnValue;
}