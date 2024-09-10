int TestCase_Comm_SendBytes::Run(int argc, char *argv[])
{
    LLBC_PrintLine("Servie send bytes test:");
    if (argc < 5)
    {
        LLBC_PrintLine("argument error, eg: ./a [client/server] [normal/raw] ip port");
        return LLBC_FAILED;
    }

    FetchArgs(argc, argv);
    LLBC_IService *svc = LLBC_IService::Create(_svcType);

    TestFacade *facade = LLBC_New(TestFacade);
    svc->RegisterFacade(facade);

    svc->Subscribe(OPCODE, facade, &TestFacade::OnRecv);

    int sid = 0;
    if (_asClient)
    {
        sid = svc->Connect(_runIp.c_str(), _runPort);
        if (sid == 0)
        {
            LLBC_FilePrintLine(stderr, "connect to %s:%d failed, err: %s",
                _runIp.c_str(), _runPort, LLBC_FormatLastError());
            LLBC_Delete(svc);

            return LLBC_FAILED;
        }

        LLBC_PrintLine("server connect to %s:%d success", _runIp.c_str(), _runPort);
    }
    else
    {
        sid = svc->Listen(_runIp.c_str(), _runPort);
        if (sid == 0)
        {
            LLBC_FilePrintLine(stderr, "failed to listen on %s:%d, err: %s",
                _runIp.c_str(), _runPort, LLBC_FormatLastError());
            LLBC_Delete(svc);

            return LLBC_FAILED;
        }

        LLBC_PrintLine("server listen on %s:%d", _runIp.c_str(), _runPort);
    }

    svc->Start();

    if (_asClient)
    {
        LLBC_Packet *pkt = LLBC_New(LLBC_Packet);
        pkt->SetHeader(sid, OPCODE, 0);
        pkt->Write("Hello, world");
        pkt->Write(0);

        svc->Send(pkt);
    }

    LLBC_PrintLine("Press any key to continue...");
    getchar();

    LLBC_Delete(svc);

    return LLBC_OK;
}