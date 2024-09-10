bool HTTPClient::beginInternal(String url, const char* expectedProtocol)
{
    DEBUG_HTTPCLIENT("[HTTP-Client][begin] url: %s\n", url.c_str());
    bool hasPort = false;
    clear();

    // check for : (http: or https:
    int index = url.indexOf(':');
    if(index < 0) {
        DEBUG_HTTPCLIENT("[HTTP-Client][begin] failed to parse protocol\n");
        return false;
    }

    _protocol = url.substring(0, index);
    url.remove(0, (index + 3)); // remove http:// or https://

    index = url.indexOf('/');
    String host = url.substring(0, index);
    url.remove(0, index); // remove host part

    // get Authorization
    index = host.indexOf('@');
    if(index >= 0) {
        // auth info
        String auth = host.substring(0, index);
        host.remove(0, index + 1); // remove auth part including @
        _base64Authorization = base64::encode(auth);
    }

    // get port
    index = host.indexOf(':');
    if(index >= 0) {
        _host = host.substring(0, index); // hostname
        host.remove(0, (index + 1)); // remove hostname + :
        _port = host.toInt(); // get port
    } else {
        _host = host;
    }
    _uri = url;
    if (_protocol != expectedProtocol) {
        DEBUG_HTTPCLIENT("[HTTP-Client][begin] unexpected protocol: %s, expected %s\n", _protocol.c_str(), expectedProtocol);
        return false;
    }
    DEBUG_HTTPCLIENT("[HTTP-Client][begin] host: %s port: %d url: %s\n", _host.c_str(), _port, _uri.c_str());
    return true;
}