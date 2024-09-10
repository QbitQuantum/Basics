// Restore thread local state to saved state in error handler `eh`.
// This is executed in two circumstances:
// * We leave a try block through normal control flow
// * An exception causes a nonlocal jump to the catch block. In this case
//   there's additional cleanup required, eg pushing the exception stack.
JL_DLLEXPORT void jl_eh_restore_state(jl_handler_t *eh)
{
    jl_ptls_t ptls = jl_get_ptls_states();
#ifdef _OS_WINDOWS_
    if (ptls->needs_resetstkoflw) {
        _resetstkoflw();
        ptls->needs_resetstkoflw = 0;
    }
#endif
    jl_task_t *current_task = ptls->current_task;
    // `eh` may be not equal to `ptls->current_task->eh`. See `jl_pop_handler`
    // This function should **NOT** have any safepoint before the ones at the
    // end.
    sig_atomic_t old_defer_signal = ptls->defer_signal;
    int8_t old_gc_state = ptls->gc_state;
    current_task->eh = eh->prev;
    ptls->pgcstack = eh->gcstack;
#ifdef JULIA_ENABLE_THREADING
    arraylist_t *locks = &current_task->locks;
    if (locks->len > eh->locks_len) {
        for (size_t i = locks->len;i > eh->locks_len;i--)
            jl_mutex_unlock_nogc((jl_mutex_t*)locks->items[i - 1]);
        locks->len = eh->locks_len;
    }
#endif
    ptls->world_age = eh->world_age;
    ptls->defer_signal = eh->defer_signal;
    ptls->gc_state = eh->gc_state;
    ptls->finalizers_inhibited = eh->finalizers_inhibited;
    if (old_gc_state && !eh->gc_state) {
        jl_gc_safepoint_(ptls);
    }
    if (old_defer_signal && !eh->defer_signal) {
        jl_sigint_safepoint(ptls);
    }
}