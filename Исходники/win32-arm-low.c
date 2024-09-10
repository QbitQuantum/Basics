static void
arm_set_thread_context (win32_thread_info *th, DEBUG_EVENT* current_event)
{
  SetThreadContext (th->h, &th->context);
}