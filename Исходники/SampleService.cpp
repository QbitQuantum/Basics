/*++

Routine Description:

    This function is executed when a Start command is sent to the
    service by the SCM or when the operating system starts (for a service
    that starts automatically). It specifies actions to take when the
    service starts. In this code sample, OnStart logs a service-start
    message to the Application log, and queues the main service function for
    execution in a thread pool worker thread.

    NOTE: A service application is designed to be long running. Therefore,
          it usually polls or monitors something in the system. The monitoring is
          set up in the OnStart method. However, OnStart does not actually do the
          monitoring. The OnStart method must return to the operating system after
          the service's operation has begun. It must not loop forever or block. To
          set up a simple monitoring mechanism, one general solution is to create
          a timer in OnStart. The timer would then raise events in your code
          periodically, at which time your service could do its monitoring. The
          other solution is to spawn a new thread to perform the main service
          functions, which is demonstrated in this code sample.

Arguments:

    Argc - The number of command line arguments

    Argv - The array of command line arguments

Return Value:

    VOID

--*/
VOID
CSampleService::OnStart(
    DWORD  Argc,
    PWSTR *Argv
    )
{
	__debugbreak();

    //
    // Log a service start message to the Application log.
    //
    WriteToEventLog(L"SampleService in OnStart", 
                    EVENTLOG_INFORMATION_TYPE);

    //
    // Set up any variables the service needs.
    //
    SetVariables();

    //
    // Set up the context, and register for notifications.
    //
    InitializeContext(&m_Context);

    //
    // Queue the main service function for execution in a worker thread.
    //
    CThreadPool::QueueUserWorkItem(&CSampleService::ServiceWorkerThread, this);
}