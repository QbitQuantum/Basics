/* BreakpointAction - Do work!
 * BreakpointAction sets the process into SINGLE_STEP mode so you can easily know when
 * the CPU finishes the instruction (Thanks to DarkStorm for this inspiration)
 * It then removes the Breakpoint and calls the callback, if present.
 */
void BreakpointAction(Breakpoint *BPX, HANDLE threadhandle)
{
   static CONTEXT context;
   memset(&context, 0, sizeof(context));

   context.ContextFlags=CONTEXT_FULL;
   GetThreadContext(threadhandle, &context);
   context.Eip=(DWORD)(LRESULT)BPX->Address;
   context.EFlags|= 0x0100; /* Single step */
   SetThreadContext(threadhandle, &context);

   RemoveBreakpoint(BPX);

   if(BPX->CallbackFunc)
      BPX->CallbackFunc(BPX->TargetProcess, BPX->dbgev, &context, BPX->type);
   return;
}