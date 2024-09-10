ssize_t MockUDPSocket::SendTo(IOVecInterface *data,
                              const ola::network::IPV4Address &ip_address,
                              unsigned short port) const {
    // This incurs a copy but it's only testing code.

    int io_len;
    const struct IOVec *iov = data->AsIOVec(&io_len);
    if (iov == NULL)
        return 0;

    unsigned int data_size = 0;
    for (int i = 0; i < io_len; i++) {
        data_size += iov[i].iov_len;
    }

    uint8_t *raw_data = new uint8_t[data_size];
    unsigned int offset = 0;
    for (int i = 0; i < io_len; i++) {
        memcpy(raw_data + offset, iov[i].iov_base, iov[i].iov_len);
        offset += iov[i].iov_len;
    }

    data->Pop(data_size);
    data->FreeIOVec(iov);
    ssize_t data_sent = SendTo(raw_data, data_size, ip_address, port);
    delete[] raw_data;
    return data_sent;
}