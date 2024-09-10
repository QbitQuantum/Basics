// "Trigger" Declarations
void join(shared_ptr<Engine> engine, string message_contents) {
    Message m = Message(rendezvous, "register", "1");
    engine->send(m);
}