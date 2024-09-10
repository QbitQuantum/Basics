ErrorCode Thread::readCPUState(Architecture::CPUState &state) {
  CONTEXT context;

  memset(&context, 0, sizeof(context));
  context.ContextFlags = CONTEXT_INTEGER |        // GP registers.
                         CONTEXT_CONTROL |        // Some more GP + CPSR.
                         CONTEXT_FLOATING_POINT | // FP registers.
                         CONTEXT_DEBUG_REGISTERS; // Debug registers.

  BOOL result = GetThreadContext(_handle, &context);
  if (!result) {
    return Platform::TranslateError();
  }

  // GP registers + CPSR.
  state.gp.r0 = context.R0;
  state.gp.r1 = context.R1;
  state.gp.r2 = context.R2;
  state.gp.r3 = context.R3;
  state.gp.r4 = context.R4;
  state.gp.r5 = context.R5;
  state.gp.r6 = context.R6;
  state.gp.r7 = context.R7;
  state.gp.r8 = context.R8;
  state.gp.r9 = context.R9;
  state.gp.r10 = context.R10;
  state.gp.r11 = context.R11;
  state.gp.ip = context.R12;
  state.gp.sp = context.Sp;
  state.gp.lr = context.Lr;
  state.gp.pc = context.Pc;
  state.gp.cpsr = context.Cpsr;

  if (state.isThumb()) {
    if (state.gp.pc & 1ULL) {
      DS2LOG(Debug, "removing thumb bit from pc and lr");
      state.gp.pc &= ~1ULL;
    } else {
      DS2LOG(Warning,
             "CPU is in thumb mode but doesn't have thumb bit set in pc");
    }
  }

  // TODO(sas): Handle floating point and debug registers.

  return kSuccess;
}