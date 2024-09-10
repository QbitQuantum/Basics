Json::Value json_socket::recv_msg() {
    char jsonsize_buf[4];
    int s = recv(this->bsock_fd, reinterpret_cast<SOCKET_BUFFER_TYPE>(&jsonsize_buf), 4, 0);

    if (s == 0)
        throw PeerDisconnected();
    else if (s < 0)
        throw ConnectionError();

    unsigned int jsonsize;
    memcpy(&jsonsize, &jsonsize_buf, 4);

    jsonsize = ntohl(jsonsize);

    char *jsonstr = new char[jsonsize + 1];
    int bytes_read = 0;

    while (bytes_read < jsonsize) {
        s = recv(this->bsock_fd, jsonstr, jsonsize, 0);

        if (s <= 0) {
            delete[] jsonstr;
            if (s == 0)
                throw PeerDisconnected();
            else
                throw ConnectionError();
        }

        bytes_read += s;
    }

    jsonstr[jsonsize] = (char)0;
    this->last_jsonstr = jsonstr;

    Json::Value root;
    Json::Reader reader;
    bool r = reader.parse(jsonstr, &jsonstr[jsonsize], root);
    if(!r) {
        cout << "Unable to parse input json: " << reader.getFormatedErrorMessages() << endl;
        cout << jsonstr << endl;

        delete[] jsonstr;
        throw NotParseableJson();
    }

    delete[] jsonstr;

    return root;
}