bool CookiesManager::GetCookies(const std::string& url, std::string* cookies)
{
    if (!cookies)
    {
        return false;
    }

    return InternalInternetGetCookie(url, cookies);
}