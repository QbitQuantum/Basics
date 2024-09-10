// "Trigger" Declarations
// Build a collection and send it to the "receiveCollection" trigger
void sendCollection(shared_ptr<Engine> engine, string) {
  K3::Collection<int> c = K3::Collection<int>(nullptr);
  for (int i =0; i < 100; i++) {
    c.insert(i);
  }

  std::string s = K3::BoostSerializer::pack(c);
  Message m = Message(K3::rendezvous, "receiveCollection", s);
  engine->send(m);
  sent = c;
}