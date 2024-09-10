FORCEINLINE
VOID
StopTraceListening (
    __in TRACEHANDLE SessionHandle,
    __inout PTRACE_PROPERTIES Properties,
    __in TRACEHANDLE ConsumingHandle
    )
{
    ControlTrace(SessionHandle, LOGGER_NAME, &Properties->TraceProperties, EVENT_TRACE_CONTROL_STOP);
    CloseTrace(ConsumingHandle);
}