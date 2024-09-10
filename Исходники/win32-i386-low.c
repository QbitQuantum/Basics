/* Find a thread record given a thread id.  If GET_CONTEXT is set then
   also retrieve the context for this thread.  */
static thread_info *
thread_rec (DWORD id, int get_context)
{
  struct thread_info *thread;
  thread_info *th;

  thread = (struct thread_info *) find_inferior_id (&all_threads, id);
  if (thread == NULL)
    return NULL;

  th = inferior_target_data (thread);
  if (!th->suspend_count && get_context)
    {
      if (get_context > 0 && id != current_event.dwThreadId)
	th->suspend_count = SuspendThread (th->h) + 1;
      else if (get_context < 0)
	th->suspend_count = -1;

      th->context.ContextFlags = CONTEXT_DEBUGGER_DR;

      GetThreadContext (th->h, &th->context);

      if (id == current_event.dwThreadId)
	{
	  /* Copy dr values from that thread.  */
	  dr[0] = th->context.Dr0;
	  dr[1] = th->context.Dr1;
	  dr[2] = th->context.Dr2;
	  dr[3] = th->context.Dr3;
	  dr[6] = th->context.Dr6;
	  dr[7] = th->context.Dr7;
	}
    }

  return th;
}