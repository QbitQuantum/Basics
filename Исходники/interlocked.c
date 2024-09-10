LONGLONG
FASTCALL
ExfInterlockedCompareExchange64(
    IN OUT LONGLONG volatile *Destination,
    IN PLONGLONG Exchange,
    IN PLONGLONG Comparand)
{
    return _InterlockedCompareExchange64(Destination, *Exchange, *Comparand);
}