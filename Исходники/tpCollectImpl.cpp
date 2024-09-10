AMDTResult tpCollectImpl::tpStartThreadProfile()
{
    AMDTResult retVal = AMDT_STATUS_OK;
    ULONG status;

    if (!tpIsProfileInitialized())
    {
        retVal = AMDT_ERROR_PROFILE_NOT_CONFIGURED;
    }

    if (tpIsProfileRunning())
    {
        retVal = AMDT_ERROR_PROFILE_ALREADY_STARTED;
    }

    PTRACEHANDLE pSessionHandle = &m_sessionHandle;
    PEVENT_TRACE_PROPERTIES pSessionProperties = m_pSessionProperties;
    bool isCollectCStack = m_callstack;

    if (NULL == pSessionProperties)
    {
        retVal = AMDT_ERROR_INTERNAL;
    }

    if (AMDT_STATUS_OK == retVal)
    {
        // Create the trace session.
        status = StartTrace(pSessionHandle, KERNEL_LOGGER_NAME, pSessionProperties);

        if (ERROR_SUCCESS == status)
        {
            // StartTrace succeeded.

            // Events in "NT Kernel Logger",
            // - EVENT_TRACE_FLAG_THREAD
            //      - Supported Event Type
            //        1   - EVENT_TRACE_TYPE_START Start thread event. The Thread_V2_TypeGroup1 MOF class defines the
            //              event data for this event
            //        2   - EVENT_TRACE_TYPE_END End thread event. The Thread_V2_TypeGroup1 MOF class defines the
            //              event data for this event
            //       36   - Context switch event. The CSwitch MOF class defines the event data for this event
            //       50   - Ready thread event. The ReadyThread MOF class defines the event data for this event
            //
            // - EVENT_TRACE_FLAG_IMAGE_LOAD
            //      - Supported Event Type
            //        10   - EVENT_TRACE_TYPE_LOAD Image load event. Generated when a DLL or executable file is loaded.
            //               The provider generates only one event for the first time a given DLL is loaded.
            //               The Image_Load MOF class defines the event data for this event
            //        2    - EVENT_TRACE_TYPE_END End thread event. Image unload event. Generated when a DLL or executable
            //               file is unloaded. The provider generates only one event for the last time a given DLL is unloaded.
            //               The Image_Load MOF class defines the event data for this event
            //
            // - EVENT_TRACE_FLAG_CSWITCH
            //      - Enables the following *Thread* event type - CSWITCH
            //        FIXME: Do i need to enable EVENT_TRACE_FLAG_THREAD or just enabling EVENT_TRACE_FLAG_CSWITCH is enough?
            //

            // StackWalk_Event class will have the stack data
            //  https://msdn.microsoft.com/en-us/library/windows/desktop/dd392323(v=vs.85).aspx
            //  CLASSIC_EVENT_ID traceCSForClasses[] = { { PerfInfoGuid, 46, { 0 } },
            //                                         { ThreadGuid, 36, { 0 } },
            //                                         { ThreadGuid, 50, { 0 } } };

            if (isCollectCStack)
            {
                CLASSIC_EVENT_ID traceCallStackForClasses[] =
                {
                    //{ g_threadGuid, 1, { 0 } },   // Start Thread Event
                    //{ g_threadGuid, 2, { 0 } },   // End Thread Event
                    { g_threadGuid, 36, { 0 } },  // Context Switch Event
                    //{ g_threadGuid, 50, { 0 } }   // Ready Thread Event
                };

                status = TraceSetInformation(*pSessionHandle,
                                             TraceStackTracingInfo,
                                             traceCallStackForClasses,
                                             sizeof(traceCallStackForClasses));

                if (ERROR_SUCCESS != status)
                {
                    retVal = AMDT_ERROR_INTERNAL;
                    fprintf(stderr, "TraceSetInformation() status(%lu)\n", status);
                }
            }
        }
        else if (ERROR_ALREADY_EXISTS == status)
        {
            retVal = AMDT_ERROR_PROFILE_SESSION_EXISTS;

            fprintf(stderr, "The NT Kernel Logger session is already in use.\n");

            // TODO: Use ControlTrace() to update
            status = ControlTraceW(0, KERNEL_LOGGER_NAME, pSessionProperties, EVENT_TRACE_CONTROL_UPDATE);
            fprintf(stderr, "ControlTraceW status(%lu).\n", status);

            if (ERROR_SUCCESS == status)
            {
                retVal = AMDT_STATUS_OK;
            }
            else
            {
                // FIXME: just for testing purpose
                status = ControlTrace(m_sessionHandle,
                                      KERNEL_LOGGER_NAME,
                                      pSessionProperties,
                                      EVENT_TRACE_CONTROL_STOP);
            }
        }
        else
        {
            retVal = AMDT_ERROR_INTERNAL;
            fprintf(stderr, "StartTrace() failed with %lu\n", status);
        }
    }

    if (AMDT_STATUS_OK == retVal)
    {
        m_tpState = AMDT_THREAD_PROFILE_STATE_STARTED;
    }

    return retVal;
} // tpStartThreadProfile