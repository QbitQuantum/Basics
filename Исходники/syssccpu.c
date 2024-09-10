VOID PhSipTickCpuDialog(
    VOID
    )
{
    ULONG64 dpcCount;
    ULONG i;

    dpcCount = 0;

    if (NT_SUCCESS(NtQuerySystemInformation(
        SystemInterruptInformation,
        InterruptInformation,
        sizeof(SYSTEM_INTERRUPT_INFORMATION) * NumberOfProcessors,
        NULL
        )))
    {
        for (i = 0; i < NumberOfProcessors; i++)
            dpcCount += InterruptInformation[i].DpcCount;
    }

    PhUpdateDelta(&ContextSwitchesDelta, PhPerfInformation.ContextSwitches);
    PhUpdateDelta(&InterruptsDelta, PhCpuTotals.InterruptCount);
    PhUpdateDelta(&DpcsDelta, dpcCount);
    PhUpdateDelta(&SystemCallsDelta, PhPerfInformation.SystemCalls);

    if (!NT_SUCCESS(NtPowerInformation(
        ProcessorInformation,
        NULL,
        0,
        PowerInformation,
        sizeof(PROCESSOR_POWER_INFORMATION) * NumberOfProcessors
        )))
    {
        memset(PowerInformation, 0, sizeof(PROCESSOR_POWER_INFORMATION) * NumberOfProcessors);
    }

    if (WindowsVersion >= WINDOWS_7)
    {
        if (PreviousPerformanceDistribution)
            PhFree(PreviousPerformanceDistribution);

        PreviousPerformanceDistribution = CurrentPerformanceDistribution;
        CurrentPerformanceDistribution = NULL;
        PhSipQueryProcessorPerformanceDistribution(&CurrentPerformanceDistribution);
    }

    CpuTicked++;

    if (CpuTicked > 2)
        CpuTicked = 2;

    PhSipUpdateCpuGraphs();
    PhSipUpdateCpuPanel();
}