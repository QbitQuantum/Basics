 void on_sendable(proton::event &e, proton::sender &s) override {
     proton::message m;
     m.body("Hello World!");
     s.send(m);
     s.close();
 }