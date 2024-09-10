void
kill_inferior (void)
{
  sim_close (gdbsim_desc, 0);
  default_callback.shutdown (&default_callback);
}