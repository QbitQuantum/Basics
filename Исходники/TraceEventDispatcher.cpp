void TraceEventDispatcher::dispatchEventOnAnyThread(char phase, const unsigned char*, const char* name, unsigned long long id,
    int numArgs, const char* const* argNames, const unsigned char* argTypes, const unsigned long long* argValues,
    unsigned char flags, double timestamp)
{
    if (phase == TRACE_EVENT_PHASE_INSTANT_WITH_SCOPE)
        phase = TRACE_EVENT_PHASE_INSTANT;
    TraceEventDispatcher* self = instance();
    {
        MutexLocker locker(self->m_mutex);
        if (self->m_handlers.find(std::make_pair(name, phase)) == self->m_handlers.end())
            return;
    }
    self->enqueueEvent(TraceEvent(timestamp, phase, name, id, currentThread(), numArgs, argNames, argTypes, argValues));
    if (isMainThread())
        self->processBackgroundEvents();
}