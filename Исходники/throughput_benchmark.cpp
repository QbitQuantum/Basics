// "Trigger" Declarations
void send_one(shared_ptr<Engine> engine, string message_contents) {
  Message m = Message(receiver, "receive_one", message);
  engine->send(m);
}