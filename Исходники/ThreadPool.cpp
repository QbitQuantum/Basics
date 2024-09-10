static unsigned __stdcall RunThread(void *arg)
{
    DebugLog << "RunThread" << std::endl;
    Thread *thread = (Thread *)arg;
    unsigned result = thread->Run();
    _endthreadex(0);
    return result;
}