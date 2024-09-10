URIBuilder::URIBuilder(const Poco::URI& uri):
    Poco::Net::NameValueCollection(HTTPUtils::getQueryMap(uri))
{
    _uri.setScheme(uri.getScheme());
    _uri.setAuthority(uri.getAuthority());
    _uri.setPath(uri.getPath());
    _uri.setFragment(uri.getFragment());
}