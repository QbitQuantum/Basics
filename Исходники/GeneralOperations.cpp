void InvokeSyscomAsOp::operator()(RLMachine& machine) {
  machine.system().invokeSyscom(machine, syscom_);
}