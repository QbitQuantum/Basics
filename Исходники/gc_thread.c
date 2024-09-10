void gc_thread_run(gc_Thread* in_thread)
{
    ResumeThread(*(HANDLE*)in_thread->threadObj);
}