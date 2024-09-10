DECLHIDDEN(int) rtR0InitNative(void)
{
    /*
     * Init the Nt cpu set.
     */
#ifdef IPRT_TARGET_NT4
    KAFFINITY ActiveProcessors = (UINT64_C(1) << KeNumberProcessors) - UINT64_C(1);
#else
    KAFFINITY ActiveProcessors = KeQueryActiveProcessors();
#endif
    RTCpuSetEmpty(&g_rtMpNtCpuSet);
    RTCpuSetFromU64(&g_rtMpNtCpuSet, ActiveProcessors);
/** @todo Port to W2K8 with > 64 cpus/threads. */

    /*
     * Initialize the function pointers.
     */
#ifdef IPRT_TARGET_NT4
    g_pfnrtNtExSetTimerResolution = NULL;
    g_pfnrtNtKeFlushQueuedDpcs = NULL;
    g_pfnrtHalRequestIpiW7Plus = NULL;
    g_pfnrtHalRequestIpiPreW7 = NULL;
    g_pfnrtNtHalSendSoftwareInterrupt = NULL;
    g_pfnrtKeIpiGenericCall = NULL;
    g_pfnrtKeInitializeAffinityEx = NULL;
    g_pfnrtKeAddProcessorAffinityEx = NULL;
    g_pfnrtKeGetProcessorIndexFromNumber = NULL;
    g_pfnrtRtlGetVersion = NULL;
    g_pfnrtKeQueryInterruptTime = NULL;
    g_pfnrtKeQueryInterruptTimePrecise = NULL;
    g_pfnrtKeQuerySystemTime = NULL;
    g_pfnrtKeQuerySystemTimePrecise = NULL;
#else
    UNICODE_STRING RoutineName;
    RtlInitUnicodeString(&RoutineName, L"ExSetTimerResolution");
    g_pfnrtNtExSetTimerResolution = (PFNMYEXSETTIMERRESOLUTION)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeFlushQueuedDpcs");
    g_pfnrtNtKeFlushQueuedDpcs = (PFNMYKEFLUSHQUEUEDDPCS)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"HalRequestIpi");
    g_pfnrtHalRequestIpiW7Plus = (PFNHALREQUESTIPI_W7PLUS)MmGetSystemRoutineAddress(&RoutineName);
    g_pfnrtHalRequestIpiPreW7 = (PFNHALREQUESTIPI_PRE_W7)g_pfnrtHalRequestIpiW7Plus;

    RtlInitUnicodeString(&RoutineName, L"HalSendSoftwareInterrupt");
    g_pfnrtNtHalSendSoftwareInterrupt = (PFNHALSENDSOFTWAREINTERRUPT)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeIpiGenericCall");
    g_pfnrtKeIpiGenericCall = (PFNRTKEIPIGENERICCALL)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeInitializeAffinityEx");
    g_pfnrtKeInitializeAffinityEx = (PFNKEINITIALIZEAFFINITYEX)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeAddProcessorAffinityEx");
    g_pfnrtKeAddProcessorAffinityEx = (PFNKEADDPROCESSORAFFINITYEX)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeGetProcessorIndexFromNumber");
    g_pfnrtKeGetProcessorIndexFromNumber = (PFNKEGETPROCESSORINDEXFROMNUMBER)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"RtlGetVersion");
    g_pfnrtRtlGetVersion = (PFNRTRTLGETVERSION)MmGetSystemRoutineAddress(&RoutineName);
# ifndef RT_ARCH_AMD64
    RtlInitUnicodeString(&RoutineName, L"KeQueryInterruptTime");
    g_pfnrtKeQueryInterruptTime = (PFNRTKEQUERYINTERRUPTTIME)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeQuerySystemTime");
    g_pfnrtKeQuerySystemTime = (PFNRTKEQUERYSYSTEMTIME)MmGetSystemRoutineAddress(&RoutineName);
# endif
    RtlInitUnicodeString(&RoutineName, L"KeQueryInterruptTimePrecise");
    g_pfnrtKeQueryInterruptTimePrecise = (PFNRTKEQUERYINTERRUPTTIMEPRECISE)MmGetSystemRoutineAddress(&RoutineName);

    RtlInitUnicodeString(&RoutineName, L"KeQuerySystemTimePrecise");
    g_pfnrtKeQuerySystemTimePrecise = (PFNRTKEQUERYSYSTEMTIMEPRECISE)MmGetSystemRoutineAddress(&RoutineName);
#endif

    /*
     * HACK ALERT! (and déjà vu warning - remember win32k.sys?)
     *
     * Try find _KPRCB::QuantumEnd and _KPRCB::[DpcData.]DpcQueueDepth.
     * For purpose of verification we use the VendorString member (12+1 chars).
     *
     * The offsets was initially derived by poking around with windbg
     * (dt _KPRCB, !prcb ++, and such like). Systematic harvesting was then
     * planned using dia2dump, grep and the symbol pack in a manner like this:
     *      dia2dump -type _KDPC_DATA -type _KPRCB EXE\ntkrnlmp.pdb | grep -wE "QuantumEnd|DpcData|DpcQueueDepth|VendorString"
     *
     * The final solution ended up using a custom harvester program called
     * ntBldSymDb that recursively searches thru unpacked symbol packages for
     * the desired structure offsets.  The program assumes that the packages
     * are unpacked into directories with the same name as the package, with
     * exception of some of the w2k packages which requires a 'w2k' prefix to
     * be distinguishable from another.
     */

    RTNTSDBOSVER OsVerInfo;
    rtR0NtGetOsVersionInfo(&OsVerInfo);

    /*
     * Gather consistent CPU vendor string and PRCB pointers.
     */
    KIRQL OldIrql;
    KeRaiseIrql(DISPATCH_LEVEL, &OldIrql); /* make sure we stay on the same cpu */

    union
    {
        uint32_t auRegs[4];
        char szVendor[4*3+1];
    } u;
    ASMCpuId(0, &u.auRegs[3], &u.auRegs[0], &u.auRegs[2], &u.auRegs[1]);
    u.szVendor[4*3] = '\0';

    uint8_t *pbPrcb;
    __try /* Warning. This try/except statement may provide some false safety. */
    {
#if defined(RT_ARCH_X86)
        PKPCR    pPcr   = (PKPCR)__readfsdword(RT_OFFSETOF(KPCR,SelfPcr));
        pbPrcb = (uint8_t *)pPcr->Prcb;
#elif defined(RT_ARCH_AMD64)
        PKPCR    pPcr   = (PKPCR)__readgsqword(RT_OFFSETOF(KPCR,Self));
        pbPrcb = (uint8_t *)pPcr->CurrentPrcb;
#else
# error "port me"
        pbPrcb = NULL;
#endif
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        pbPrcb = NULL;
    }

    /*
     * Search the database
     */
    if (pbPrcb)
    {
        /* Find the best matching kernel version based on build number. */
        uint32_t iBest      = UINT32_MAX;
        int32_t  iBestDelta = INT32_MAX;
        for (uint32_t i = 0; i < RT_ELEMENTS(g_artNtSdbSets); i++)
        {
            if (g_artNtSdbSets[i].OsVerInfo.fChecked != OsVerInfo.fChecked)
                continue;
            if (OsVerInfo.fSmp /*must-be-smp*/ && !g_artNtSdbSets[i].OsVerInfo.fSmp)
                continue;

            int32_t iDelta = RT_ABS((int32_t)OsVerInfo.uBuildNo - (int32_t)g_artNtSdbSets[i].OsVerInfo.uBuildNo);
            if (   iDelta == 0
                && (g_artNtSdbSets[i].OsVerInfo.uCsdNo == OsVerInfo.uCsdNo || OsVerInfo.uCsdNo == MY_NIL_CSD))
            {
                /* prefect */
                iBestDelta = iDelta;
                iBest      = i;
                break;
            }
            if (   iDelta < iBestDelta
                || iBest == UINT32_MAX
                || (   iDelta == iBestDelta
                    && OsVerInfo.uCsdNo != MY_NIL_CSD
                    &&   RT_ABS(g_artNtSdbSets[i    ].OsVerInfo.uCsdNo - (int32_t)OsVerInfo.uCsdNo)
                       < RT_ABS(g_artNtSdbSets[iBest].OsVerInfo.uCsdNo - (int32_t)OsVerInfo.uCsdNo)
                   )
                )
            {
                iBestDelta = iDelta;
                iBest      = i;
            }
        }
        if (iBest < RT_ELEMENTS(g_artNtSdbSets))
        {
            /* Try all sets: iBest -> End; iBest -> Start. */
            bool    fDone = false;
            int32_t i     = iBest;
            while (   i < RT_ELEMENTS(g_artNtSdbSets)
                   && !(fDone = rtR0NtTryMatchSymSet(&g_artNtSdbSets[i], pbPrcb, u.szVendor, &OsVerInfo)))
                i++;
            if (!fDone)
            {
                i = (int32_t)iBest - 1;
                while (   i >= 0
                       && !(fDone = rtR0NtTryMatchSymSet(&g_artNtSdbSets[i], pbPrcb, u.szVendor, &OsVerInfo)))
                    i--;
            }
        }
        else
            DbgPrint("IPRT: Failed to locate data set.\n");
    }
    else
        DbgPrint("IPRT: Failed to get PCBR pointer.\n");

    KeLowerIrql(OldIrql); /* Lowering the IRQL early in the hope that we may catch exceptions below. */

#ifndef IN_GUEST
    if (!g_offrtNtPbQuantumEnd && !g_offrtNtPbDpcQueueDepth)
        DbgPrint("IPRT: Neither _KPRCB::QuantumEnd nor _KPRCB::DpcQueueDepth was not found! Kernel %u.%u %u %s\n",
                 OsVerInfo.uMajorVer, OsVerInfo.uMinorVer, OsVerInfo.uBuildNo, OsVerInfo.fChecked ? "checked" : "free");
# ifdef DEBUG
    else
        DbgPrint("IPRT: _KPRCB:{.QuantumEnd=%x/%d, .DpcQueueDepth=%x/%d} Kernel %u.%u %u %s\n",
                 g_offrtNtPbQuantumEnd, g_cbrtNtPbQuantumEnd, g_offrtNtPbDpcQueueDepth,
                 OsVerInfo.uMajorVer, OsVerInfo.uMinorVer, OsVerInfo.uBuildNo, OsVerInfo.fChecked ? "checked" : "free");
# endif
#endif

    /*
     * Special IPI fun for RTMpPokeCpu.
     *
     * On Vista and later the DPC method doesn't seem to reliably send IPIs,
     * so we have to use alternative methods.  The NtHalSendSoftwareInterrupt
     * is preferrable, but it's AMD64 only.  The NalRequestIpip method changed
     * in Windows 7 with the lots-of-processors-support, but it's the only
     * targeted IPI game in town if we cannot use KeInsertQueueDpc.  Worst case
     * we use broadcast IPIs.
     */
    if (   OsVerInfo.uMajorVer > 6
        || (OsVerInfo.uMajorVer == 6 && OsVerInfo.uMinorVer > 0))
        g_pfnrtHalRequestIpiPreW7 = NULL;
    else
        g_pfnrtHalRequestIpiW7Plus = NULL;

    g_pfnrtMpPokeCpuWorker = rtMpPokeCpuUsingDpc;
#ifndef IPRT_TARGET_NT4
    if (g_pfnrtNtHalSendSoftwareInterrupt)
        g_pfnrtMpPokeCpuWorker = rtMpPokeCpuUsingHalSendSoftwareInterrupt;
    else if (   g_pfnrtHalRequestIpiW7Plus
             && g_pfnrtKeInitializeAffinityEx
             && g_pfnrtKeAddProcessorAffinityEx
             && g_pfnrtKeGetProcessorIndexFromNumber)
        g_pfnrtMpPokeCpuWorker = rtMpPokeCpuUsingHalReqestIpiW7Plus;
    else if (OsVerInfo.uMajorVer >= 6 && g_pfnrtKeIpiGenericCall)
        g_pfnrtMpPokeCpuWorker = rtMpPokeCpuUsingBroadcastIpi;
    /* else: Windows XP should send always send an IPI -> VERIFY */
#endif

    return VINF_SUCCESS;
}