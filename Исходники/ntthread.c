void
_PR_MD_CREATE_PRIMORDIAL_USER_THREAD(PRThread *thread)
{
    thread->md.fiber_id = ConvertThreadToFiber(NULL);
    PR_ASSERT(thread->md.fiber_id);
    _MD_SET_CURRENT_THREAD(thread);
    _MD_SET_LAST_THREAD(thread);
    thread->no_sched = 1;
    return;
}