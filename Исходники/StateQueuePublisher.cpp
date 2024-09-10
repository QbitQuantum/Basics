//  Sends string as 0MQ string, as multipart non-terminal
static bool
s_sendmore (zmq::socket_t & socket, const std::string & data)
{
  char * buff = (char*)malloc(data.size());
  memcpy(buff, data.c_str(), data.size());
  zmq::message_t message((void*)buff, data.size(), s_free, 0);
  bool rc = socket.send(message, ZMQ_SNDMORE);
  return (rc);
}