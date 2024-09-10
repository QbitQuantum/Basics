bool ObjectMutator::operator()(RLMachine& machine, GraphicsObject& object) {
  unsigned int ticks = machine.system().event().getTicks();
  PerformSetting(machine, object);
  return ticks > (creation_time_ + delay_ + duration_time_);
}