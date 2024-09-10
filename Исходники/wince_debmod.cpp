//--------------------------------------------------------------------------
ea_t wince_debmod_t::is_hwbpt_triggered(thid_t id, bool /*is_stepping*/)
{
  if ( is_xscale )
  {
    uint32 dcsr = SetDebugControlAndStatus(0, 0);
    int moe = (dcsr >> 2) & 7;  // method of entry (exception reason)
    //    msg("moe=%d\n", moe);
    switch ( moe )
    {
    case 1: // Instruction Breakpoint Hit
    case 2: // Data Breakpoint Hit
      {
        SetDebugControlAndStatus(0, 7<<2); // clean moe
        CONTEXT Context;
        Context.ContextFlags = CONTEXT_CONTROL;
        HANDLE h = get_thread_handle(id);
        if ( GetThreadContext(h, &Context) )
        {
          ea_t ea = s0tops(Context.Pc);
          if ( s0tops(codebpts[0]) == ea || s0tops(codebpts[1]) == ea )
          {
            //              msg("HARDWARE CODE BREAKPOINT!\n");
            return ea;
          }
          // This is a data breakpoint
          // Set PC to the next instruction since the data bpts always occur
          // AFTER the instruction
#define THUMB_STATE 0x0020
          Context.Pc += (Context.Psr & THUMB_STATE)? 2 : 4;
          SetThreadContext(h, &Context);
        }
        // FIXME: determine which data bpt really caused the exception
        // Currently we just return the first active bpt
        return databpts[0] != BADADDR ? databpts[0] : databpts[1];
      }
    case 0: // Processor Reset
    case 3: // BKPT Instruction Executed
    case 4: // External Debug Event (JTAG Debug Break or SOC Debug Break)
    case 5: // Vector Trap Occurred
    case 6: // Trace Buffer Full Break
    case 7: // Reserved
      break;
    }
  }
  return BADADDR;
}