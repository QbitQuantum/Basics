DysectAPI::DysectErrorCode TargetVar::getValue(ConditionResult& result, Value& c, Process::const_ptr process, Dyninst::THR_ID tid) {

  ProcDebug *processState = NULL;
  vector<THR_ID> threads;
  int ret;

  Walker* proc = (Walker*)process->getData();
  if(!proc) {
    return DYSECTWARN(Error, "Walker not found for process: %d", process->getPid());
  }

  DataLocation* dataLoc;


  if(!DataLocation::findVariable(process, proc, name, dataLoc)) {
    // Variable not found
    return DYSECTWARN(Error, "Variable '%s' not found", name.c_str());
  }

  Value nc;
  DysectAPI::DysectErrorCode code = dataLoc->getValue(nc);

  if (nc.getType() == Value::longType)
    DYSECTVERBOSE(true, "Read long value for %s: %ld", name.c_str(), nc.getValue<long>());
  else if (nc.getType() == Value::intType)
    DYSECTVERBOSE(true, "Read int value for %s: %d", name.c_str(), nc.getValue<int>());
  else if (nc.getType() == Value::floatType)
    DYSECTVERBOSE(true, "Read float value for %s: %f", name.c_str(), nc.getValue<float>());
  else if (nc.getType() == Value::doubleType)
    DYSECTVERBOSE(true, "Read double value for %s: %f", name.c_str(), nc.getValue<double>());
  else if (nc.getType() == Value::pointerType)
    DYSECTVERBOSE(true, "Read pointer value for %s: %lx", name.c_str(), nc.getValue<long>());

  if(code != OK)
    return code;

  c.copy(nc);
  result = Resolved;

  return DysectAPI::OK;
}