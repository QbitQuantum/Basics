LONG
WINAPI
redirect_InterlockedCompareExchange (
    __inout __drv_interlocked LONG volatile *Destination,
    __in LONG ExChange,
    __in LONG Comperand
    )
{
    return _InterlockedCompareExchange(Destination, ExChange, Comperand);
}