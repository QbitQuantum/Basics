ssize_t socket_send_buffers(cutils_socket_t sock,
                            const cutils_socket_buffer_t* buffers,
                            size_t num_buffers) {
    if (num_buffers > SOCKET_SEND_BUFFERS_MAX_BUFFERS) {
        return -1;
    }

    WSABUF wsa_buffers[SOCKET_SEND_BUFFERS_MAX_BUFFERS];
    for (size_t i = 0; i < num_buffers; ++i) {
        // It's safe to cast away const here; WSABUF declares non-const
        // void* because it's used for both send and receive, but since
        // we're only sending, the data won't be modified.
        wsa_buffers[i].buf =
                reinterpret_cast<char*>(const_cast<void*>(buffers[i].data));
        wsa_buffers[i].len = buffers[i].length;
    }

    DWORD bytes_sent = 0;
    if (WSASend(sock, wsa_buffers, num_buffers, &bytes_sent, 0, nullptr,
                nullptr) != SOCKET_ERROR) {
        return bytes_sent;
    }

    return -1;
}