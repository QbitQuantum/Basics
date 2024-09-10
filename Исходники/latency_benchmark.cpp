// "Trigger" Declarations
void warmup_stor(shared_ptr<Engine> engine, string message_contents) {
  std::cout << "received warmup" << std::endl;
  Message m = Message(sender, "warmup_rtos", "()");
  engine->send(m);
}