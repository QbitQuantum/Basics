static FORCEINLINE VOID
__WriteMemoryBarrier()
{
    KeMemoryBarrier();
    _WriteBarrier();
}