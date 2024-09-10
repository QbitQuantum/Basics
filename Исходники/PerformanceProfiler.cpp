void ProfilerTimeRecordToBuffer(const char* eventDescription, const long long beginClock, const long long endClock)
{
    std::lock_guard<std::mutex> lock(g_mutex);

    if (!g_profilerState->enabled)
        return;

    auto eventDescriptionBytes = strlen(eventDescription) + 1;
    auto requiredBufferBytes = eventDescriptionBytes + sizeof(CustomEventRecord);
    if ((g_profilerState->customEventOffset + requiredBufferBytes) > g_profilerState->customEventBufferBytes)
    {
        if (!g_profilerState->customEventBufferFull)
        {
            fprintf(stderr, "Warning: Performance Profiler: Buffer is full, no more events will be recorded.\n");
            g_profilerState->customEventBufferFull = true;
        }
        return;
    }

    strcpy(g_profilerState->customEventBuffer.get() + g_profilerState->customEventOffset, eventDescription);
    g_profilerState->customEventOffset += eventDescriptionBytes;

    CustomEventRecord eventRecord;
    eventRecord.beginClock = beginClock;
    eventRecord.endClock = endClock;
    eventRecord.threadId = GetThreadId();

    memcpy(g_profilerState->customEventBuffer.get() + g_profilerState->customEventOffset, &eventRecord, sizeof(CustomEventRecord));
    g_profilerState->customEventOffset += sizeof(CustomEventRecord);
}