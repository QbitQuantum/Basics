int
App::Main()
{
    FNET_SignalShutDown::hookSignals();
    // would like to turn off FNET logging somehow
    if (_argc < 3) {
        fprintf(stderr, "usage: %s <listenspec> <connectspec> [verbose]\n", _argv[0]);
        return 1;
    }
    bool verbose = (_argc > 3) && (strcmp(_argv[3], "verbose") == 0);

    FRT_Supervisor supervisor;
    RPCProxy       proxy(supervisor, _argv[2], verbose);

    supervisor.GetReflectionManager()->Reset();
    supervisor.SetSessionInitHook(FRT_METHOD(RPCProxy::HOOK_Init), &proxy);
    supervisor.SetSessionDownHook(FRT_METHOD(RPCProxy::HOOK_Down), &proxy);
    supervisor.SetSessionFiniHook(FRT_METHOD(RPCProxy::HOOK_Fini), &proxy);
    supervisor.SetMethodMismatchHook(FRT_METHOD(RPCProxy::HOOK_Mismatch),
                                     &proxy);
    supervisor.Listen(_argv[1]);
    FNET_SignalShutDown ssd(*supervisor.GetTransport());
    supervisor.Main();
    return 0;
}