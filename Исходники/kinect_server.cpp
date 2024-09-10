 void on_message(connection_ptr con, message_ptr msg) {
     if(msg->get_payload()=="skeleton") {
         con->send(getImageData(),msg->get_opcode());
     } else if(msg->get_payload()=="depth") {
         con->send(getDepthMap(true),msg->get_opcode());
     } else if(msg->get_payload()=="rgb") {
         con->send(getRGBImage(true),msg->get_opcode());
     } else if(msg->get_payload()=="savergb") {
         con->send(saveRGBImage(),msg->get_opcode());
     } else if(msg->get_payload()=="savedepth") {
         con->send(saveDepthMap(),msg->get_opcode());
     } else {
         con->send("Unknown client request",msg->get_opcode());
     }
 }