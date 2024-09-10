static void create_stdin_waiter_thread(void)
{
    netsnmp_assert(s_thread_handle == 0);
    s_thread_handle = (HANDLE)_beginthreadex(0, 0, wait_for_stdin, 0, 0, &s_threadid);
    netsnmp_assert(s_thread_handle != 0);
}