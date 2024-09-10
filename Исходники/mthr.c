void
__mingwthr_run_key_dtors (void)
{
    __mingwthr_key_t *keyp;

#ifdef DEBUG
    printf ("%s: Entering Thread id %ld\n", __FUNCTION__, GetCurrentThreadId() );
#endif

    EnterCriticalSection (&__mingwthr_cs);

    for (keyp = key_dtor_list; keyp; )
    {
        LPVOID value = TlsGetValue (keyp->key);
        if (GetLastError () == ERROR_SUCCESS)
        {
#ifdef DEBUG
            printf ("   (%ld, %x)\n", keyp->key, keyp->dtor);
#endif
            if (value)
                (*keyp->dtor) (value);
        }
#ifdef DEBUG
        else
        {
            printf ("   TlsGetValue FAILED  (%ld, %x)\n",
                    keyp->key, keyp->dtor);
        }
#endif
        keyp = keyp->next;
    }

    LeaveCriticalSection (&__mingwthr_cs);

#ifdef DEBUG
    printf ("%s: Exiting Thread id %ld\n", __FUNCTION__, GetCurrentThreadId() );
#endif
}