/**
 * Retrieves the value of the instruction pointer in a given thread.
 *
 * @param tid The thread ID of the thread.
 * @param addr The variable where the value of the instruction pointer is stored.
 *
 * @return A NaviError code that describes whether the operation was successful or not.
 */
NaviError LinuxSystem::getInstructionPointer(unsigned int tid,
                                             CPUADDRESS& addr) {


  msglog->log(LOG_VERBOSE, "Trying to read the instruction pointer");

  user_regs_struct regs;

  if (ptrace(PTRACE_GETREGS, getPID(), 0, &regs)) {
    msglog->log(LOG_ALWAYS, "get_eip: PTRACE_GETREGS: %s", strerror(errno));
    return NaviErrors::COULDNT_READ_REGISTERS;
  }

  addr = regs.eip;

  return NaviErrors::SUCCESS;
}