void Host::Initialize(int argc, const char** argv)
{
    eventWindow = new EventWindow();
    mainThreadId = GetCurrentThreadId();
    OleInitialize(0);
    this->AddMessageHandler(&MainThreadJobsTickleHandler);

#ifndef DEBUG
    // only create a debug console when not compiled in debug mode
    // otherwise, it should be autocreated
    if (this->DebugModeEnabled())
    {
        RedirectIOToConsole();
    }
#endif
}