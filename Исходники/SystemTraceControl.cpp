int
__cdecl
wmain()
{
    CLASSIC_EVENT_ID EventId[2];
    ULONG Status = ERROR_SUCCESS;
    TRACEHANDLE SessionHandle = 0;
    PEVENT_TRACE_PROPERTIES TraceProperties;
    BOOLEAN TraceStarted = FALSE;
    ULONG SystemTraceFlags[8];
    PWSTR LoggerName = L"MyTrace";

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    //
    // Allocate EVENT_TRACE_PROPERTIES structure and perform some
    // basic initialization. 
    //
    // N.B. LoggerName will be populated during StartTrace call.
    //

    TraceProperties = AllocateTraceProperties(NULL, L"SystemTrace.etl");
    if (TraceProperties == NULL) {
        Status = ERROR_OUTOFMEMORY;
        goto Exit;
    }

    //
    // Configure additinal trace settings.
    //

    TraceProperties->LogFileMode = EVENT_TRACE_FILE_MODE_SEQUENTIAL | EVENT_TRACE_SYSTEM_LOGGER_MODE;
    TraceProperties->Wnode.ClientContext = 1; // Use QueryPerformanceCounter for time stamps
    TraceProperties->MaximumFileSize = 100; // Limit file size to 100MB max
    TraceProperties->BufferSize = 512; // Use 512KB trace buffers
    TraceProperties->MinimumBuffers = 64;
    TraceProperties->MaximumBuffers = 128;
    
    //
    // Start trace session which can receive events from SystemTraceProvider.
    //
    
    Status = StartTrace(&SessionHandle, LoggerName, TraceProperties);
    if (Status != ERROR_SUCCESS) {
        wprintf(L"StartTrace() failed with %lu\n", Status);
        goto Exit;
    }

    TraceStarted = TRUE;

    //
    // Configure stack walking. In this example stack traces will be collected on
    // ImageLoad and ProcessCreate events.
    //
    // N.B. Stack tracing is configured before enabling event collection.
    //    
    
    ZeroMemory(EventId, sizeof(EventId));
    EventId[0].EventGuid = ImageLoadGuid;
    EventId[0].Type =  EVENT_TRACE_TYPE_LOAD;
    EventId[1].EventGuid = ProcessGuid;
    EventId[1].Type = EVENT_TRACE_TYPE_START;
    
    Status = TraceSetInformation(SessionHandle,
                                 TraceStackTracingInfo,
                                 EventId,
                                 sizeof(EventId));

    if (Status != ERROR_SUCCESS) {
        wprintf(L"TraceSetInformation(StackTracing) failed with %lu\n", Status);
        goto Exit;
    }
    
    //
    // Enable system events for Process, Thread and Loader groups.
    //

    ZeroMemory(SystemTraceFlags, sizeof(SystemTraceFlags));
    SystemTraceFlags[0] = (EVENT_TRACE_FLAG_PROCESS | 
                           EVENT_TRACE_FLAG_THREAD |
                           EVENT_TRACE_FLAG_IMAGE_LOAD);
    
    Status = TraceSetInformation(SessionHandle, 
                                 TraceSystemTraceEnableFlagsInfo,
                                 SystemTraceFlags,
                                 sizeof(SystemTraceFlags));
    
    if (Status != ERROR_SUCCESS) {
        wprintf(L"TraceSetInformation(EnableFlags) failed with %lu\n", Status);
        goto Exit;
    }
    
    //
    // Collect trace for 30 seconds.
    //

    Sleep(30 * 1000);

Exit:

    //
    // Stop tracing.
    //

    if (TraceStarted != FALSE) {
        Status = ControlTrace(SessionHandle, NULL, TraceProperties, EVENT_TRACE_CONTROL_STOP);  
        if (Status != ERROR_SUCCESS) {
            wprintf(L"StopTrace() failed with %lu\n", Status);
        }
    }

    if (TraceProperties != NULL) {
        FreeTraceProperties(TraceProperties);
    }

    return Status;
}