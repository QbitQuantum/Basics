// Locks this processor until g_ReleaseAllProcessors becomes 1.
_Use_decl_annotations_ EXTERN_C static
void ExclpRaiseIrqlAndWaitDpc(
    PKDPC Dpc,
    PVOID DeferredContext,
    PVOID SystemArgument1,
    PVOID SystemArgument2)
{
    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    // Increase the number of locked processors.
    _InterlockedIncrement(&g_ExclpNumberOfLockedProcessors);

    // Wait until g_ReleaseAllProcessors becomes 1.
    while (!_InterlockedCompareExchange(&g_ExclpReleaseAllProcessors, 1, 1))
    {
        KeStallExecutionProcessor(10);
    }

    // Decrease the number of locked processors.
    _InterlockedDecrement(&g_ExclpNumberOfLockedProcessors);
}