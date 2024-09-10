void
sys_thread_switch (struct sys_thread *td)
{
  sys_vm2_leave(td);
#ifndef _WIN32
  sched_yield();
#else
  SwitchToThread();
#endif
  sys_vm2_enter(td);
}