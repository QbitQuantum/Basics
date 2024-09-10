LONG CExeModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0)
    {
        if (CoSuspendClassObjects() == S_OK)
            PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
    }
    return l;
}