static void
__mingwthr_run_key_dtors (void)
{
  __mingwthr_key_t volatile *keyp;

  if (__mingwthr_cs_init == 0)
    return;
  EnterCriticalSection (&__mingwthr_cs);

  for (keyp = key_dtor_list; keyp; )
    {
      LPVOID value = TlsGetValue (keyp->key);
      if (GetLastError () == ERROR_SUCCESS)
        {
          if (value)
            (*keyp->dtor) (value);
        }
      keyp = keyp->next;
    }

  LeaveCriticalSection (&__mingwthr_cs);
}