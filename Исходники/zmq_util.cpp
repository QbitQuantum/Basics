/*
 * return number of bytes sent, negative if error
 */
int send_msg(zmq::socket_t &sock, uint8_t *data, size_t len, int flag){
  
  int nbytes;
  try{
    nbytes = sock.send(data, len, flag);
  }catch(zmq::error_t e){
    //LOG(NOR, stderr, "send failed: %s\n", e.what());
    return -1;
  }
  return nbytes;
}