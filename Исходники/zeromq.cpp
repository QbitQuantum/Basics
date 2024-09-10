int SendEnvelope(socket_t &socket, Envelope &e, bool is_protocol, int flags)
{
    message_t msg;

    if (is_protocol) {
        if (!e.ToProtocolZmqMessage(msg)) return -1;
    }
    else {
        if (!e.ToZmqMessage(msg)) return -1;
    }

    return socket.send(msg, flags) ? 1 : 0;
}