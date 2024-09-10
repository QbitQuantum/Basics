/**
 * Register active event listener for the selected VM.
 *
 * @param   virtualBox ptr to IVirtualBox object
 * @param   session    ptr to ISession object
 */
static void registerActiveEventListener(IVirtualBox *virtualBox, ISession *session)
{
    IConsole *console = NULL;
    HRESULT rc;

    rc = ISession_get_Console(session, &console);
    if ((SUCCEEDED(rc)) && console)
    {
        IEventSource *es = NULL;
        rc = IConsole_get_EventSource(console, &es);
        if (SUCCEEDED(rc) && es)
        {
            static const ULONG s_auInterestingEvents[] =
            {
                VBoxEventType_OnMousePointerShapeChanged,
                VBoxEventType_OnMouseCapabilityChanged,
                VBoxEventType_OnKeyboardLedsChanged,
                VBoxEventType_OnStateChanged,
                VBoxEventType_OnAdditionsStateChanged,
                VBoxEventType_OnNetworkAdapterChanged,
                VBoxEventType_OnSerialPortChanged,
                VBoxEventType_OnParallelPortChanged,
                VBoxEventType_OnStorageControllerChanged,
                VBoxEventType_OnMediumChanged,
                VBoxEventType_OnVRDEServerChanged,
                VBoxEventType_OnUSBControllerChanged,
                VBoxEventType_OnUSBDeviceStateChanged,
                VBoxEventType_OnSharedFolderChanged,
                VBoxEventType_OnRuntimeError,
                VBoxEventType_OnCanShowWindow,
                VBoxEventType_OnShowWindow
            };
            SAFEARRAY *interestingEventsSA = NULL;
            IEventListenerDemo *consoleListener = NULL;

            /* The VirtualBox API expects enum values as VT_I4, which in the
             * future can be hopefully relaxed. */
            interestingEventsSA = g_pVBoxFuncs->pfnSafeArrayCreateVector(VT_I4, 0,
                                                                           sizeof(s_auInterestingEvents)
                                                                         / sizeof(s_auInterestingEvents[0]));
            g_pVBoxFuncs->pfnSafeArrayCopyInParamHelper(interestingEventsSA, &s_auInterestingEvents,
                                                        sizeof(s_auInterestingEvents));

            consoleListener = calloc(1, sizeof(IEventListenerDemo));
            if (consoleListener)
            {
                consoleListener->lpVtbl = &(g_IEventListenerDemoVtblInt.lpVtbl);
#ifdef WIN32
                CoCreateFreeThreadedMarshaler((IUnknown *)consoleListener, &consoleListener->pUnkMarshaler);
#endif
                IEventListenerDemo_AddRef(consoleListener);

                rc = IEventSource_RegisterListener(es, (IEventListener *)consoleListener,
                                                   ComSafeArrayAsInParam(interestingEventsSA),
                                                   1 /* active */);
                if (SUCCEEDED(rc))
                {
                    /* Just wait here for events, no easy way to do this better
                     * as there's not much to do after this completes. */
                    printf("Entering event loop, PowerOff the machine to exit or press Ctrl-C to terminate\n");
                    fflush(stdout);
#ifdef WIN32
                    SetConsoleCtrlHandler(ctrlCHandler, TRUE);
#else
                    signal(SIGINT, (void (*)(int))ctrlCHandler);
#endif

                    while (!g_fStop)
                        g_pVBoxFuncs->pfnProcessEventQueue(250);

#ifdef WIN32
                    SetConsoleCtrlHandler(ctrlCHandler, FALSE);
#else
                    signal(SIGINT, SIG_DFL);
#endif
                }
                else
                    printf("Failed to register event listener.\n");
                IEventSource_UnregisterListener(es, (IEventListener *)consoleListener);
#ifdef WIN32
                if (consoleListener->pUnkMarshaler)
                    IUnknown_Release(consoleListener->pUnkMarshaler);
#endif
                IEventListenerDemo_Release(consoleListener);
            }
            else
                printf("Failed while allocating memory for console event listener.\n");
            g_pVBoxFuncs->pfnSafeArrayDestroy(interestingEventsSA);
            IEventSource_Release(es);
        }
        else
            printf("Failed to get the event source instance.\n");
        IConsole_Release(console);
    }
}