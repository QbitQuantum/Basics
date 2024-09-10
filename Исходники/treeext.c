VOID UpdateThreadClrData(
    _In_ PTHREAD_TREE_CONTEXT Context,
    _Inout_ PDN_THREAD_ITEM DnThread
    )
{
    if (!DnThread->ClrDataValid)
    {
        IXCLRDataProcess *process;
        IXCLRDataTask *task;
        IXCLRDataAppDomain *appDomain;

        if (Context->Support)
            process = Context->Support->DataProcess;
        else
            return;

        if (SUCCEEDED(IXCLRDataProcess_GetTaskByOSThreadID(process, HandleToUlong(DnThread->ThreadItem->ThreadId), &task)))
        {
            if (SUCCEEDED(IXCLRDataTask_GetCurrentAppDomain(task, &appDomain)))
            {
                DnThread->AppDomainText = GetNameXClrDataAppDomain(appDomain);
                IXCLRDataAppDomain_Release(appDomain);
            }

            IXCLRDataTask_Release(task);
        }

        DnThread->ClrDataValid = TRUE;
    }
}