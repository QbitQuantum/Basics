static void
set_step_threads (int threadId, int trace)
{
  int rv, tix;
  HANDLE thread = lookup_thread_id (threadId, &tix);

  rv = GetThreadContext (thread, &context);
  if (rv != -1)
    {
      thread_step_flags[tix] = trace;
      if (trace)
	context.EFlags |= 0x100; /* TRAP (single step) flag */
      else
	context.EFlags &= ~0x100; /* TRAP (single step) flag */
      SetThreadContext (thread, &context);
    }
}