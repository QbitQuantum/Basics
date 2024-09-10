/** we store our host name once */
std::string getHostNameCached() {
    std::string temp = _hostNameCached.get();
    if (_hostNameCached.empty()) {
        temp = getHostName();
        _hostNameCached = temp;
    }
    return temp;
}