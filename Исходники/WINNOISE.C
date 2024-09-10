/*
 * This function is called on a timer, and it will monitor
 * frequently changing quantities such as the state of physical and
 * virtual memory, the state of the process's message queue, which
 * window is in the foreground, which owns the clipboard, etc.
 */
void noise_regular(void)
{
    HWND w;
    DWORD z;
    POINT pt;
    MEMORYSTATUS memstat;
    FILETIME times[4];

    w = GetForegroundWindow();
    random_add_noise(NOISE_SOURCE_FGWINDOW, &w, sizeof(w));
    w = GetCapture();
    random_add_noise(NOISE_SOURCE_CAPTURE, &w, sizeof(w));
    w = GetClipboardOwner();
    random_add_noise(NOISE_SOURCE_CLIPBOARD, &w, sizeof(w));
    z = GetQueueStatus(QS_ALLEVENTS);
    random_add_noise(NOISE_SOURCE_QUEUE, &z, sizeof(z));

    GetCursorPos(&pt);
    random_add_noise(NOISE_SOURCE_CURSORPOS, &pt, sizeof(pt));

    GlobalMemoryStatus(&memstat);
    random_add_noise(NOISE_SOURCE_MEMINFO, &memstat, sizeof(memstat));

    GetThreadTimes(GetCurrentThread(), times, times + 1, times + 2,
		   times + 3);
    random_add_noise(NOISE_SOURCE_THREADTIME, &times, sizeof(times));
    GetProcessTimes(GetCurrentProcess(), times, times + 1, times + 2,
		    times + 3);
    random_add_noise(NOISE_SOURCE_PROCTIME, &times, sizeof(times));
}