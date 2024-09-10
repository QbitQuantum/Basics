SilcThread silc_thread_self(void)
{
#ifdef SILC_THREADS
  SilcWin32Thread self = TlsGetValue(silc_thread_tls);

  if (!self) {
    /* This should only happen for the main thread. */
    HANDLE handle = GetCurrentThread ();
    HANDLE process = GetCurrentProcess ();
    self = silc_calloc(1, sizeof(*self));
    DuplicateHandle(process, handle, process,
		    &self->thread, 0, FALSE,
		    DUPLICATE_SAME_ACCESS);
    TlsSetValue(silc_thread_tls, self);
  }

  return (SilcThread)self;
#else
  return NULL;
#endif
}