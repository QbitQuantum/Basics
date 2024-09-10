static FORCEINLINE VOID
xen_wmb()
{
    KeMemoryBarrier();
    _WriteBarrier();
}