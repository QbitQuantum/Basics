RTDECL(bool) RTThreadPreemptIsPending(RTTHREAD hThread)
{
    Assert(hThread == NIL_RTTHREAD); RT_NOREF1(hThread);

    /*
     * Read the globals and check if they are useful.
     */
/** @todo Should we check KPRCB.InterruptRequest and KPRCB.DpcInterruptRequested (older kernels).  */
    uint32_t const offQuantumEnd     = g_offrtNtPbQuantumEnd;
    uint32_t const cbQuantumEnd      = g_cbrtNtPbQuantumEnd;
    uint32_t const offDpcQueueDepth  = g_offrtNtPbDpcQueueDepth;
    if (!offQuantumEnd && !cbQuantumEnd && !offDpcQueueDepth)
        return false;
    Assert((offQuantumEnd && cbQuantumEnd) || (!offQuantumEnd && !cbQuantumEnd));

    /*
     * Disable interrupts so we won't be messed around.
     */
    bool            fPending;
    RTCCUINTREG     fSavedFlags  = ASMIntDisableFlags();

#ifdef RT_ARCH_X86
    PKPCR       pPcr   = (PKPCR)__readfsdword(RT_OFFSETOF(KPCR,SelfPcr));
    uint8_t    *pbPrcb = (uint8_t *)pPcr->Prcb;

#elif defined(RT_ARCH_AMD64)
    /* HACK ALERT! The offset is from windbg/vista64. */
    PKPCR       pPcr   = (PKPCR)__readgsqword(RT_OFFSETOF(KPCR,Self));
    uint8_t    *pbPrcb = (uint8_t *)pPcr->CurrentPrcb;

#else
# error "port me"
#endif

    /* Check QuantumEnd. */
    if (cbQuantumEnd == 1)
    {
        uint8_t volatile *pbQuantumEnd = (uint8_t volatile *)(pbPrcb + offQuantumEnd);
        fPending = *pbQuantumEnd == TRUE;
    }
    else if (cbQuantumEnd == sizeof(uint32_t))
    {
        uint32_t volatile *pu32QuantumEnd = (uint32_t volatile *)(pbPrcb + offQuantumEnd);
        fPending = *pu32QuantumEnd != 0;
    }
    else
        fPending = false;

    /* Check DpcQueueDepth. */
    if (    !fPending
        &&  offDpcQueueDepth)
    {
        uint32_t volatile *pu32DpcQueueDepth = (uint32_t volatile *)(pbPrcb + offDpcQueueDepth);
        fPending = *pu32DpcQueueDepth > 0;
    }

    ASMSetFlags(fSavedFlags);
    return fPending;
}