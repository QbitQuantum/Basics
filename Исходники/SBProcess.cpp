bool
SBProcess::SetSelectedThread (const SBThread &thread)
{
    ProcessSP process_sp(GetSP());
    if (process_sp)
    {
        Mutex::Locker api_locker (process_sp->GetTarget().GetAPIMutex());
        return process_sp->GetThreadList().SetSelectedThreadByID (thread.GetThreadID());
    }
    return false;
}