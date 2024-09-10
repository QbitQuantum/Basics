EXTERN_C FORCEINLINE
ULONG
CounterInitialize(
    __in_opt PERFLIBREQUEST NotificationCallback,
    __in_opt PERF_MEM_ALLOC MemoryAllocationFunction,
    __in_opt PERF_MEM_FREE MemoryFreeFunction,
    __inout_opt PVOID MemoryFunctionsContext
    )
{
    ULONG Status;
    PERF_PROVIDER_CONTEXT ProviderContext;

    ZeroMemory(&ProviderContext, sizeof(PERF_PROVIDER_CONTEXT));
    ProviderContext.ContextSize = sizeof(PERF_PROVIDER_CONTEXT);
    ProviderContext.ControlCallback = NotificationCallback;
    ProviderContext.MemAllocRoutine = MemoryAllocationFunction;
    ProviderContext.MemFreeRoutine = MemoryFreeFunction;
    ProviderContext.pMemContext = MemoryFunctionsContext;

    Status = PerfStartProviderEx(&YardmasterGuid,
                                 &ProviderContext,
                                 &Yardmaster);
    if (Status != ERROR_SUCCESS) {
        Yardmaster = NULL;
        return Status;
    }

    Status = PerfSetCounterSetInfo(Yardmaster,
                                   &PerformanceInfo.CounterSet,
                                   sizeof PerformanceInfo);
    if (Status != ERROR_SUCCESS) {
        CounterCleanup();
        return Status;
    }
    return ERROR_SUCCESS;
}