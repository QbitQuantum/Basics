static void
end_callbacks (void)
{
  if (callbacks_initialized)
    {
      gdb_callback.shutdown (&gdb_callback);
      callbacks_initialized = 0;
    }
}