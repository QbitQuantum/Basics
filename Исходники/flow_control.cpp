 void send_available_messages(proton::sender &s) {
     for (int i = sequence; available && s.credit() > 0; i++) {
         std::ostringstream mbody;
         mbody << "flow_sender message " << sequence++;
         proton::message m(mbody.str());
         s.send(m);
         available--;
     }
 }