VOID
NTAPI
INIT_FUNCTION
KiSystemStartupBootStack(VOID)
{
    PKTHREAD Thread;

    /* Initialize the kernel for the current CPU */
    KiInitializeKernel(&KiInitialProcess.Pcb,
                       (PKTHREAD)KeLoaderBlock->Thread,
                       (PVOID)(KeLoaderBlock->KernelStack & ~3),
                       (PKPRCB)__readfsdword(KPCR_PRCB),
                       KeNumberProcessors - 1,
                       KeLoaderBlock);

    /* Set the priority of this thread to 0 */
    Thread = KeGetCurrentThread();
    Thread->Priority = 0;

    /* Force interrupts enabled and lower IRQL back to DISPATCH_LEVEL */
    _enable();
    KfLowerIrql(DISPATCH_LEVEL);

    /* Set the right wait IRQL */
    Thread->WaitIrql = DISPATCH_LEVEL;

    /* Jump into the idle loop */
    KiIdleLoop();
}