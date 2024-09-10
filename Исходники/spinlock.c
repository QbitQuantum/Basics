VOID
NTAPI
HalpAcquireCmosSpinLock(VOID)
{
    ULONG_PTR Flags;

    /* Get flags and disable interrupts */
    Flags = __readeflags();
    _disable();

    /* Acquire the lock */
    KxAcquireSpinLock(&HalpSystemHardwareLock);

    /* We have the lock, save the flags now */
    HalpSystemHardwareFlags = Flags;
}