/**
 * Parse the arguments.
 *
 * @returns 0 on success, fully bitched exit code on failure.
 *
 * @param   argc    Argument count.
 * @param   argv    Argument vector.
 */
int VBoxNetBaseService::parseArgs(int argc, char **argv)
{

    RTGETOPTSTATE State;
    PRTGETOPTDEF paOptionArray = getOptionsPtr();
    int rc = RTGetOptInit(&State, argc, argv, paOptionArray, m_vecOptionDefs.size(), 0, 0 /*fFlags*/);
    AssertRCReturn(rc, 49);
#if 0
    /* default initialization */
    m_enmTrunkType = kIntNetTrunkType_WhateverNone;
#endif
    Log2(("BaseService: parseArgs enter\n"));

    for (;;)
    {
        RTGETOPTUNION Val;
        rc = RTGetOpt(&State, &Val);
        if (!rc)
            break;
        switch (rc)
        {
            case 'N':
                m_Name = Val.psz;
                break;
            case 'n':
                m_Network = Val.psz;
                break;
            case 't':
                m_TrunkName = Val.psz;
                break;
            case 'T':
                if (!strcmp(Val.psz, "none"))
                    m_enmTrunkType = kIntNetTrunkType_None;
                else if (!strcmp(Val.psz, "whatever"))
                    m_enmTrunkType = kIntNetTrunkType_WhateverNone;
                else if (!strcmp(Val.psz, "netflt"))
                    m_enmTrunkType = kIntNetTrunkType_NetFlt;
                else if (!strcmp(Val.psz, "netadp"))
                    m_enmTrunkType = kIntNetTrunkType_NetAdp;
                else if (!strcmp(Val.psz, "srvnat"))
                    m_enmTrunkType = kIntNetTrunkType_SrvNat;
                else
                {
                    RTStrmPrintf(g_pStdErr, "Invalid trunk type '%s'\n", Val.psz);
                    return 1;
                }
                break;
            case 'a':
                m_MacAddress = Val.MacAddr;
                break;
            case 'i':
                m_Ipv4Address = Val.IPv4Addr;
                break;
        case 'm':
          m_Ipv4Netmask = Val.IPv4Addr;
          break;

            case 'v':
                m_cVerbosity++;
                break;

            case 'V':
                RTPrintf("%sr%u\n", RTBldCfgVersion(), RTBldCfgRevision());
                return 1;

            case 'h':
                RTPrintf("%s Version %sr%u\n"
                         "(C) 2009-" VBOX_C_YEAR " " VBOX_VENDOR "\n"
                         "All rights reserved.\n"
                         "\n"
                         "Usage: %s <options>\n"
                         "\n"
                         "Options:\n",
                         RTProcShortName(),
                         RTBldCfgVersion(),
                         RTBldCfgRevision(),
                         RTProcShortName());
                for (unsigned int i = 0; i < m_vecOptionDefs.size(); i++)
                    RTPrintf("    -%c, %s\n", m_vecOptionDefs[i]->iShort, m_vecOptionDefs[i]->pszLong);
                usage(); /* to print Service Specific usage */
                return 1;

            default:
                int rc1 = parseOpt(rc, Val);
                if (RT_FAILURE(rc1))
                {
                    rc = RTGetOptPrintError(rc, &Val);
                    RTPrintf("Use --help for more information.\n");
                    return rc;
                }
        }
    }

    RTMemFree(paOptionArray);
    return rc;
}