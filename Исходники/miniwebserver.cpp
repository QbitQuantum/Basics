void MiniWebServer::accepted(boost::shared_ptr<Socket> psock, long long connectionId) {
    char buf[4096];
    int len = 0;
    try {
#ifdef MONGO_SSL
        psock->doSSLHandshake();
#endif
        psock->setTimeout(8);
        while (1) {
            int left = sizeof(buf) - 1 - len;
            if (left == 0)
                break;
            int x;
            try {
                x = psock->unsafe_recv(buf + len, left);
            } catch (const SocketException&) {
                psock->close();
                return;
            }
            len += x;
            buf[len] = 0;
            if (fullReceive(buf)) {
                break;
            }
        }
    } catch (const SocketException& e) {
        LOG(1) << "couldn't recv data via http client: " << e << endl;
        return;
    }
    buf[len] = 0;

    string responseMsg;
    int responseCode = 599;
    vector<string> headers;

    try {
        doRequest(buf, parseURL(buf), responseMsg, responseCode, headers, psock->remoteAddr());
    } catch (std::exception& e) {
        responseCode = 500;
        responseMsg = "error loading page: ";
        responseMsg += e.what();
    } catch (...) {
        responseCode = 500;
        responseMsg = "unknown error loading page";
    }

    stringstream ss;
    ss << "HTTP/1.0 " << responseCode;
    if (responseCode == 200)
        ss << " OK";
    ss << "\r\n";
    if (headers.empty()) {
        ss << "Content-Type: text/html\r\n";
    } else {
        for (vector<string>::iterator i = headers.begin(); i != headers.end(); i++) {
            verify(strncmp("Content-Length", i->c_str(), 14));
            ss << *i << "\r\n";
        }
    }
    ss << "Connection: close\r\n";
    ss << "Content-Length: " << responseMsg.size() << "\r\n";
    ss << "\r\n";
    ss << responseMsg;
    string response = ss.str();

    try {
        psock->send(response.c_str(), response.size(), "http response");
        psock->close();
    } catch (SocketException& e) {
        LOG(1) << "couldn't send data to http client: " << e << endl;
    }
}