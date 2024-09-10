StatusWith<ConnectionString> ConnectionString::parse(const std::string& url) {
    const std::string::size_type i = url.find('/');

    // Replica set
    if (i != std::string::npos && i != 0) {
        return ConnectionString(SET, url.substr(i + 1), url.substr(0, i));
    }

    const int numCommas = str::count(url, ',');

    // Single host
    if (numCommas == 0) {
        HostAndPort singleHost;
        Status status = singleHost.initialize(url);
        if (!status.isOK()) {
            return status;
        }

        return ConnectionString(singleHost);
    }

    // Sharding config server
    if (numCommas == 2) {
        return ConnectionString(SYNC, url, "");
    }

    return Status(ErrorCodes::FailedToParse, str::stream() << "invalid url [" << url << "]");
}