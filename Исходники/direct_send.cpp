 void on_sendable(proton::event &e, proton::sender &sender) override {
     while (sender.credit() && sent < total) {
         proton::message msg;
         msg.id(sent + 1);
         std::map<std::string, int> m;
         m["sequence"] = sent+1;
         msg.body(m);
         sender.send(msg);
         sent++;
     }
 }