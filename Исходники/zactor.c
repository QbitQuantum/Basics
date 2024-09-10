zactor_t *
zactor_new (zactor_fn *actor, void *args)
{
    zactor_t *self = (zactor_t *) zmalloc (sizeof (zactor_t));
    if (!self)
        return NULL;
    self->tag = ZACTOR_TAG;

    shim_t *shim = (shim_t *) zmalloc (sizeof (shim_t));
    if (!shim) {
        zactor_destroy (&self);
        return NULL;
    }
    shim->pipe = zsys_create_pipe (&self->pipe);
    shim->handler = actor;
    shim->args = args;

#if defined (__UNIX__)
    pthread_t thread;
    pthread_create (&thread, NULL, s_thread_shim, shim);
    pthread_detach (thread);

#elif defined (__WINDOWS__)
    HANDLE handle = (HANDLE) _beginthreadex (
        NULL,                   //  Handle is private to this process
        0,                      //  Use a default stack size for new thread
        &s_thread_shim,         //  Start real thread function via this shim
        shim,                   //  Which gets arguments shim
        CREATE_SUSPENDED,       //  Set thread priority before starting it
        NULL);                  //  We don't use the thread ID
    assert (handle);

    //  Set child thread priority to same as current
    int priority = GetThreadPriority (GetCurrentThread ());
    SetThreadPriority (handle, priority);

    //  Start thread & release resources
    ResumeThread (handle);
    CloseHandle (handle);
#endif

    //  Mandatory handshake for new actor so that constructor returns only
    //  when actor has also initialized. This eliminates timing issues at
    //  application start up.
    zsock_wait (self->pipe);
    return self;
}