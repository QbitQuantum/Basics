// capacity request
void process_status_request(zmq::socket_t& status, int& number_of_workers) {
  // null request
  zmq::message_t incoming_msg;
  status.recv(&incoming_msg);

  // send current capacity
  zmq::message_t status_msg(sizeof(number_of_workers));
  memcpy(status_msg.data(), &number_of_workers, sizeof(number_of_workers));
  status.send(status_msg);
}