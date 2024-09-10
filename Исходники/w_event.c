/**
 * Notify all waiters and reset state to non-signaled
 */
Bool EVENT_Pulse(Event * e) 
{
    if (!PulseEvent(e->handle)) {
        ASSMSG1("PulseEvent() failed, error %lu", GetLastError());
        return False;
    }
    return True;
}