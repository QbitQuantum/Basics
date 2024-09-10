void sendOverSocket(zmq::socket_t &socket, const message::Node &msg) {
  std::string msg_str;
  msg.SerializeToString(&msg_str);

  zmq::message_t request(msg_str.size());
  memcpy((void*)request.data(), msg_str.c_str(), msg_str.size());

  // Sometimes sending will fail with EINTR.  In this case, we try to
  // send the message again.
  while (true) {
    int failed_attempts = 0;
    try {
      bool sentOK = socket.send(request);
      // If sentOK is false, there was an EAGAIN.  We handle this the
      // same as EINTR.
      if (!sentOK) {
        failed_attempts++;
        if (failed_attempts > 10) abort();
        continue;
      }
      // Success: stop the loop.
      break;
    } catch (zmq::error_t &e) {
      failed_attempts++;
      if (failed_attempts > 10) abort();
      if (e.num() == EINTR) {
        continue;
      }
      // If it was something other than EINTR, rethrow the exception.
      throw e;
    }
  }
}