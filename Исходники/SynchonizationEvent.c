BOOL
WINAPI
StSynchronizationEvent_IsSet (
    __in PST_SYNCHRONIZATION_EVENT Event
)
{
    LONG State = Event->State;
    _ReadBarrier();
    return (State != 0);
}