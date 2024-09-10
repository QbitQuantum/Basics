static void 
traphandler(int sig, siginfo_t *si, void *UC)
{
  ucontext_t *uc = UC;

  if(extra_traphandler != NULL && !extra_traphandler(sig, si, UC))
    return;
    
  static void *frames[MAXFRAMES];
  char buf[256];
  int nframes = backtrace(frames, MAXFRAMES);
  const char *reason = NULL;

  TRAPMSG("Signal: %d in %s ", sig, line1);

  switch(sig) {
  case SIGSEGV:
    switch(si->si_code) {
    case SEGV_MAPERR:  reason = "Address not mapped"; break;
    case SEGV_ACCERR:  reason = "Access error"; break;
    }
    break;

  case SIGFPE:
    switch(si->si_code) {
    case FPE_INTDIV:  reason = "Integer division by zero"; break;
    }
    break;
  }

  addr2text(buf, sizeof(buf), si->si_addr);

  TRAPMSG("Fault address %s (%s)", buf, reason ?: "N/A");

  TRAPMSG("Loaded libraries: %s ", libs);

#if defined(__arm__) 
  TRAPMSG("   trap_no = %08lx", uc->uc_mcontext.trap_no);
  TRAPMSG("error_code = %08lx", uc->uc_mcontext.error_code);
  TRAPMSG("   oldmask = %08lx", uc->uc_mcontext.oldmask);
  TRAPMSG("        R0 = %08lx", uc->uc_mcontext.arm_r0);
  TRAPMSG("        R1 = %08lx", uc->uc_mcontext.arm_r1);
  TRAPMSG("        R2 = %08lx", uc->uc_mcontext.arm_r2);
  TRAPMSG("        R3 = %08lx", uc->uc_mcontext.arm_r3);
  TRAPMSG("        R4 = %08lx", uc->uc_mcontext.arm_r4);
  TRAPMSG("        R5 = %08lx", uc->uc_mcontext.arm_r5);
  TRAPMSG("        R6 = %08lx", uc->uc_mcontext.arm_r6);
  TRAPMSG("        R7 = %08lx", uc->uc_mcontext.arm_r7);
  TRAPMSG("        R8 = %08lx", uc->uc_mcontext.arm_r8);
  TRAPMSG("        R9 = %08lx", uc->uc_mcontext.arm_r9);
  TRAPMSG("       R10 = %08lx", uc->uc_mcontext.arm_r10);
  TRAPMSG("        FP = %08lx", uc->uc_mcontext.arm_fp);
  TRAPMSG("        IP = %08lx", uc->uc_mcontext.arm_ip);
  TRAPMSG("        SP = %08lx", uc->uc_mcontext.arm_sp);
  TRAPMSG("        LR = %08lx", uc->uc_mcontext.arm_lr);
  TRAPMSG("        PC = %08lx", uc->uc_mcontext.arm_pc);
  TRAPMSG("      CPSR = %08lx", uc->uc_mcontext.arm_cpsr);
  TRAPMSG("fault_addr = %08lx", uc->uc_mcontext.fault_address);

#else
  char tmpbuf[1024];
  snprintf(tmpbuf, sizeof(tmpbuf), "Register dump [%d]: ", NGREG);
  int i;
  for(i = 0; i < NGREG; i++) {
#if __WORDSIZE == 64
    sappend(tmpbuf, sizeof(tmpbuf), "%016llx ", uc->uc_mcontext.gregs[i]);
#else
    sappend(tmpbuf, sizeof(tmpbuf), "%08x ", uc->uc_mcontext.gregs[i]);
#endif
  }
  TRAPMSG("%s", tmpbuf);
#endif

  dumpstack(frames, nframes);
  _exit(8);
}