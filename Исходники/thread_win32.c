static void
native_cond_wait(rb_thread_cond_t *cond, rb_thread_lock_t *mutex)
{
    DWORD r;
    struct cond_event_entry entry;
//RHO	
    //WinMo BUG: in release mode CreateEventW without name inside non-main thread does not work
    static int nCounter = 0;
    wchar_t buf[20];
    wsprintfW(buf, L"REvent%d", nCounter);
    nCounter = nCounter + 1;

    entry.next = 0;
    entry.event = CreateEventW(0, FALSE, FALSE, buf);
//RHO

    /* cond is guarded by mutex */
    if (cond->next) {
	cond->last->next = &entry;
	cond->last = &entry;
    }
    else {
	cond->next = &entry;
	cond->last = &entry;
    }

    native_mutex_unlock(mutex);
    {
	r = WaitForSingleObject(entry.event, INFINITE);
	if (r != WAIT_OBJECT_0) {
	    rb_bug("native_cond_wait: WaitForSingleObject returns %lu", r);
	}
    }
    native_mutex_lock(mutex);

    w32_close_handle(entry.event);
}