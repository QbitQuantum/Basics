void set_thread_exception_handlers()
{
    set_terminate(handle_terminate);
    set_unexpected(handle_unexpected);
    signal(SIGABRT, handle_signal);
    signal(SIGFPE, handle_signal);
    signal(SIGILL, handle_signal);
    signal(SIGSEGV, handle_signal);
}