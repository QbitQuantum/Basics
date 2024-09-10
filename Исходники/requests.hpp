bool recursive_receive(zmq::socket_t& receiving_socket, zmq::message_t& message,
                       const REQ& req, RES& response, bool& succeed) {
  bool rc = receiving_socket.recv(&message);

  if (rc) {
    auto serialized_resp = kZmqUtil->message_to_string(message);
    response.ParseFromString(serialized_resp);

    if (req.request_id() == response.response_id()) {
      succeed = true;
      return false;
    } else {
      return true;
    }
  } else {
    // timeout
    if (errno == EAGAIN) {
      succeed = false;
    } else {
      succeed = false;
    }

    return false;
  }
}