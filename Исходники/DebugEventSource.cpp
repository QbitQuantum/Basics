void DebugEventSource::SendCustomEvent(void* payload, int length)
{
    if (!EventEnabled(DEBUG_EVENT_TYPE_CUSTOM))
        return;
    DebugEventPayload rawPayload;
    rawPayload.type = DEBUG_EVENT_TYPE_CUSTOM;
    rawPayload.Custom.payload = (CORDB_ADDRESS)payload;
    rawPayload.Custom.length = length;
    SendRawEvent(&rawPayload);
}