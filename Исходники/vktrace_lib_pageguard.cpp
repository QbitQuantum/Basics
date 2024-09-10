void removePageGuardExceptionHandler()
{
    vktrace_sem_wait(ref_amount_sem_id);
    if (OPTHandler)
    {
        if (OPTHandlerRefAmount)
        {
            OPTHandlerRefAmount--;
        }
        if (!OPTHandlerRefAmount)
        {
            RemoveVectoredExceptionHandler(OPTHandler);
            OPTHandler = nullptr;
        }
    }
    vktrace_sem_post(ref_amount_sem_id);
}