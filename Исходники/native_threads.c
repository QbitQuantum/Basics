static void native_thread_exit(struct c_state *c_state)
{
  DIAGNOSTIC(2,"leaving native thread",0,0);
  ExitThread(0);
}