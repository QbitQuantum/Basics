bool
Control::processSetPriorityLevel(int process_nbr, priorityLevel priority)
{
  strstream strm;
  Process* process = getProcess(process_nbr);

  if (process == NULL) {
    strm << "Process: " << process_nbr << " not reachable!" << ends;
    theUI->showMsg(strm.str());
    return false;
  }

  ProcessId pid = process->getProcessId();

  strm << "Process:  " << process_nbr << " (PID " << pid << ") priority being set to " << priority << ends;
  theUI->showMsg(strm.str());

  process->setPriorityLevel(priority);

  return true;
}