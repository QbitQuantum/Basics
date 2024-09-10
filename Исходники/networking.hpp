    static bool recv_zmq_message(zmq::socket_t& sock,
                                 zmq::message_t& msg,
                                 T& object,
                                 int flags = ZMQ_NOBLOCK)
    {
        if (!sock.recv(&msg, flags)) {
            return false;
        }

        memcpy(&object, msg.data(), msg.size());
        return true;
    }