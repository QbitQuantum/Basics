 void on_message(connection_ptr con,message_ptr msg) {
     int value = atoi(msg->get_payload().c_str());
     
     if (value == 0) {
         con->send("invalid sleep value.");
     } else {
         request r;
         r.con = con;
         r.value = value;
         m_coordinator.add_request(r);
     }
 }