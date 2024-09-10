void recv_multipart(zmq::socket_t &socket) {
    int64_t more=-1;
    size_t more_size = sizeof (more);
    while(more) {
        zmq::message_t response;
        socket.recv(&response);

        std::string response_str((const char *)response.data(),
                                                             response.size());
        cout << response_str << endl;

        socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);
    }
}