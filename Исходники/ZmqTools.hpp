 /**
  * Receive message part from socket
  */
 inline void
 recv_msg(zmq::socket_t& sock, zmq::message_t& msg,
   int flags = 0) throw(ZmqErrorType)
 {
   try
   {
     if (!sock.recv(&msg, flags))
     {
       throw zmq::error_t();
     }
   }
   catch (const zmq::error_t& e)
   {
     throw_zmq_exception(e);
   }
 }