omni_thread::init_t::init_t(void)
{
    if (count++ != 0)   // only do it once however many objects get created.
    return;

    DB(cerr << "omni_thread::init: NT implementation initialising\n");

    self_tls_index = TlsAlloc();

    if (self_tls_index == 0xffffffff)
    throw omni_thread_fatal(GetLastError());

    next_id_mutex = new omni_mutex;

    //
    // Create object for this (i.e. initial) thread.
    //

    omni_thread* t = new omni_thread;

    t->_state = STATE_RUNNING;

    if (!DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
             GetCurrentProcess(), &t->handle,
             0, FALSE, DUPLICATE_SAME_ACCESS))
    throw omni_thread_fatal(GetLastError());

    t->nt_id = GetCurrentThreadId();

    DB(cerr << "initial thread " << t->id() << " NT thread id " << t->nt_id
       << endl);

    if (!TlsSetValue(self_tls_index, (LPVOID)t))
    throw omni_thread_fatal(GetLastError());

    if (!SetThreadPriority(t->handle, nt_priority(PRIORITY_NORMAL)))
    throw omni_thread_fatal(GetLastError());
}