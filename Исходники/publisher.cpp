static bool
s_sendobj (zmq::socket_t & socket, Message& obj) {

    msgPtr message = obj.fillmessage();

    bool rc = socket.send (*message);
    return (rc);
}