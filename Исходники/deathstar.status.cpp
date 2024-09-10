void process_frontend(zmq::socket_t& frontend, int& available_workers) {
  zmq::message_t req;
  frontend.recv(&req);
  zmq::message_t reply(sizeof(available_workers));
  memcpy(reply.data(), &available_workers, sizeof(available_workers));
  frontend.send(reply);
}