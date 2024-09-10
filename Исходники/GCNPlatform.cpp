void GCNPlatform::InvokeSyscom(RLMachine& machine, int syscom) {
  machine.system().invokeSyscom(machine, syscom);
}