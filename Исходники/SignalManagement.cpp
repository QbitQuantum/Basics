{
    std::cerr << "Watchdog timer expired: Scilab killed" << std::endl;
    ExitProcess(1);
}
void timeout_process_after(int timeoutDelay)
{
    auto timerid = CreateThreadpoolTimer(kill_process_callback, nullptr, nullptr);

    FILETIME FileDueTime;
    ULARGE_INTEGER ulDueTime;

    // Set the timer to fire in the delay in seconds
    ulDueTime.QuadPart = (ULONGLONG) - (timeoutDelay * 10 * 1000 * 1000);
    FileDueTime.dwHighDateTime = ulDueTime.HighPart;