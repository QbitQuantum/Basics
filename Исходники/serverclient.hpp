	static bool s_sendmore(zmq::socket_t &socket, const std::string &msg)
	{
		zmq::message_t message(msg.size());
		memcpy(message.data(), msg.data(), msg.size());

		bool sent = socket.send(message, ZMQ_SNDMORE);
		return sent;
	}