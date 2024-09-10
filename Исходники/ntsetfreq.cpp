RT_C_DECLS_END



int main(int argc, char **argv)
{
    int rc = RTR3InitExe(argc, &argv, 0);
    if (RT_FAILURE(rc))
        return RTMsgInitFailure(rc);

    /*
     * Parse arguments.
     */
    bool        fVerbose   = true;
    uint32_t    u32NewRes  = 0;
    uint32_t    cSecsSleep = UINT32_MAX;

    static const RTGETOPTDEF s_aOptions[] =
    {
        { "--resolution",  'r', RTGETOPT_REQ_UINT32 },
        { "--sleep",       's', RTGETOPT_REQ_UINT32 },
        { "--quiet",       'q', RTGETOPT_REQ_NOTHING },
        { "--verbose",     'v', RTGETOPT_REQ_NOTHING },
    };

    RTGETOPTUNION ValueUnion;
    RTGETOPTSTATE GetState;
    RTGetOptInit(&GetState, argc, argv, s_aOptions, RT_ELEMENTS(s_aOptions), 1, 0);
    while ((rc = RTGetOpt(&GetState, &ValueUnion)))
    {
        switch (rc)
        {
            case 'r':
                u32NewRes = ValueUnion.u32;
                if (u32NewRes > 16*10000 /* 16 ms */ || u32NewRes < 1000 /* 100 microsec */)
                    return RTMsgErrorExit(RTEXITCODE_SYNTAX,
                                          "syntax error: the new timer resolution (%RU32) is out of range\n",
                                          u32NewRes);
                break;

            case 's':
                cSecsSleep = ValueUnion.u32;
                break;

            case 'q':
                fVerbose = false;
                break;

            case 'v':
                fVerbose = true;
                break;

            case 'h':
                RTPrintf("Usage: ntsetfreq [-q|--quiet] [-v|--verbose] [-r|--resolution <100ns>] [-s|--sleep <1s>]\n");
                return RTEXITCODE_SUCCESS;

            default:
                return RTGetOptPrintError(rc, &ValueUnion);
        }
    }


    /*
     * Query the current resolution.
     */
    ULONG   Cur = ~0;
    ULONG   Min = ~0;
    ULONG   Max = ~0;
    LONG    Status;
    if (fVerbose || !u32NewRes)
    {
        Status = NtQueryTimerResolution(&Min, &Max, &Cur);
        if (Status >= 0)
            RTMsgInfo("cur: %u (%u.%02u Hz)  min: %u (%u.%02u Hz)  max: %u (%u.%02u Hz)\n",
                      Cur, 10000000 / Cur, (10000000 / (Cur * 100)) % 100,
                      Min, 10000000 / Min, (10000000 / (Min * 100)) % 100,
                      Max, 10000000 / Max, (10000000 / (Max * 100)) % 100);
        else
            RTMsgError("NTQueryTimerResolution failed with status %#x\n", Status);
    }

    if (u32NewRes)
    {
        Status = NtSetTimerResolution(u32NewRes, TRUE, &Cur);
        if (Status < 0)
            RTMsgError("NTSetTimerResolution(%RU32,,) failed with status %#x\n", u32NewRes, Status);
        else if (fVerbose)
        {
            Cur = Min = Max = ~0;
            Status = NtQueryTimerResolution(&Min, &Max, &Cur);
            if (Status >= 0)
                RTMsgInfo("new: %u (%u.%02u Hz) requested %RU32 (%u.%02u Hz)\n",
                          Cur, 10000000 / Cur, (10000000 / (Cur * 100)) % 100,
                          u32NewRes, 10000000 / u32NewRes, (10000000 / (u32NewRes * 100)) % 100);
            else
                RTMsgError("NTSetTimerResolution succeeded but the NTQueryTimerResolution call failed with status %#x (ignored)\n", Status);
            Status = 0;
        }
    }

    if (u32NewRes && Status >= 0)
    {
        if (cSecsSleep == UINT32_MAX)
            for (;;)
                RTThreadSleep(RT_INDEFINITE_WAIT);
        else
            while (cSecsSleep-- > 0)
                RTThreadSleep(1000);
    }

    return Status >= 0 ? 0 : 1;
}