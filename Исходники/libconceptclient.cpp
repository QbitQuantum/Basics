DLL_EXPORT int UDPFriend(void *client, char *host_data, char *buf, int buf_size) {
    CConceptClient *CC = (CConceptClient *)client;
    if ((CC) && (buf_size > 0) && (buf)) {
        AnsiString temp = InitUDP3(CC, host_data);
        int size = temp.Length();
        if (size >= buf_size)
            size = buf_size - 1;
        memcpy(buf, temp.c_str(), size);
        buf[size] = 0;
        return size;
    }
    return 0;
}