   bool recv(zmq::socket_t & socket) {
      clear();
      while(1) {
         zmq::message_t message(0);
         try {
            if (!socket.recv(&message, 0)) {
               return false;
            }
         } catch (zmq::error_t error) {
            //std::cout << "E: " << error.what() << std::endl;
            return false;
         }
         char *data = reinterpret_cast<char*>(message.data());
         if (message.size() == 17 && data[0] == 0) {
            push_back(encode_uuid(msg_to_string(message)));
         } else {
            push_back(msg_to_string(message));
         }
		 boost::int64_t more;
         size_t more_size = sizeof(more);
         socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);
         if (!more) {
            break;
         }
      }
      return true;
   }