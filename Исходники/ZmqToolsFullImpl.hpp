 int
 relay_raw(zmq::socket_t& src, zmq::socket_t& dst, bool check_first_part)
 {
   int relayed = 0;
   for (
     bool more = check_first_part ? has_more(src) : true;
     more; ++relayed)
   {
     zmq::message_t cur_part;
     src.recv(&cur_part);
     more = has_more(src);
     int flag = more ? ZMQ_SNDMORE : 0;
     send_msg(dst, cur_part, flag);
   }
   return relayed;
 }