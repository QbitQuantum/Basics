/**
 * Synchronizes one GDT entry (guest -> shadow).
 *
 * @returns VBox strict status code (appropriate for trap handling and GC
 *          return).
 * @retval  VINF_SUCCESS
 * @retval  VINF_EM_RAW_EMULATE_INSTR_GDT_FAULT
 * @retval  VINF_SELM_SYNC_GDT
 *
 * @param   pVM         Pointer to the VM.
 * @param   pVCpu       The current virtual CPU.
 * @param   pCtx        CPU context for the current CPU.
 * @param   iGDTEntry   The GDT entry to sync.
 *
 * @remarks Caller checks that this isn't the LDT entry!
 */
static VBOXSTRICTRC selmRCSyncGDTEntry(PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx, unsigned iGDTEntry)
{
    Log2(("GDT %04X LDTR=%04X\n", iGDTEntry, CPUMGetGuestLDTR(pVCpu)));

    /*
     * Validate the offset.
     */
    VBOXGDTR GdtrGuest;
    CPUMGetGuestGDTR(pVCpu, &GdtrGuest);
    unsigned offEntry = iGDTEntry * sizeof(X86DESC);
    if (    iGDTEntry >= SELM_GDT_ELEMENTS
        ||  offEntry  >  GdtrGuest.cbGdt)
        return VINF_SUCCESS; /* ignore */

    /*
     * Read the guest descriptor.
     */
    X86DESC Desc;
    int rc = MMGCRamRead(pVM, &Desc, (uint8_t *)(uintptr_t)GdtrGuest.pGdt + offEntry, sizeof(X86DESC));
    if (RT_FAILURE(rc))
    {
        rc = PGMPhysSimpleReadGCPtr(pVCpu, &Desc, (uintptr_t)GdtrGuest.pGdt + offEntry, sizeof(X86DESC));
        if (RT_FAILURE(rc))
        {
            VMCPU_FF_SET(pVCpu, VMCPU_FF_SELM_SYNC_GDT);
            VMCPU_FF_SET(pVCpu, VMCPU_FF_TO_R3); /* paranoia */
            /* return VINF_EM_RESCHEDULE_REM; - bad idea if we're in a patch. */
            return VINF_EM_RAW_EMULATE_INSTR_GDT_FAULT;
        }
    }

    /*
     * Check for conflicts.
     */
    RTSEL   Sel = iGDTEntry << X86_SEL_SHIFT;
    Assert(   !(pVM->selm.s.aHyperSel[SELM_HYPER_SEL_CS]         & ~X86_SEL_MASK_OFF_RPL)
           && !(pVM->selm.s.aHyperSel[SELM_HYPER_SEL_DS]         & ~X86_SEL_MASK_OFF_RPL)
           && !(pVM->selm.s.aHyperSel[SELM_HYPER_SEL_CS64]       & ~X86_SEL_MASK_OFF_RPL)
           && !(pVM->selm.s.aHyperSel[SELM_HYPER_SEL_TSS]        & ~X86_SEL_MASK_OFF_RPL)
           && !(pVM->selm.s.aHyperSel[SELM_HYPER_SEL_TSS_TRAP08] & ~X86_SEL_MASK_OFF_RPL));
    if (    pVM->selm.s.aHyperSel[SELM_HYPER_SEL_CS]         == Sel
        ||  pVM->selm.s.aHyperSel[SELM_HYPER_SEL_DS]         == Sel
        ||  pVM->selm.s.aHyperSel[SELM_HYPER_SEL_CS64]       == Sel
        ||  pVM->selm.s.aHyperSel[SELM_HYPER_SEL_TSS]        == Sel
        ||  pVM->selm.s.aHyperSel[SELM_HYPER_SEL_TSS_TRAP08] == Sel)
    {
        if (Desc.Gen.u1Present)
        {
            Log(("selmRCSyncGDTEntry: Sel=%d Desc=%.8Rhxs: detected conflict!!\n", Sel, &Desc));
            VMCPU_FF_SET(pVCpu, VMCPU_FF_SELM_SYNC_GDT);
            VMCPU_FF_SET(pVCpu, VMCPU_FF_TO_R3);
            return VINF_SELM_SYNC_GDT;  /** @todo this status code is ignored, unfortunately. */
        }
        Log(("selmRCSyncGDTEntry: Sel=%d Desc=%.8Rhxs: potential conflict (still not present)!\n", Sel, &Desc));

        /* Note: we can't continue below or else we'll change the shadow descriptor!! */
        /* When the guest makes the selector present, then we'll do a GDT sync. */
        return VINF_SUCCESS;
    }

    /*
     * Convert the guest selector to a shadow selector and update the shadow GDT.
     */
    selmGuestToShadowDesc(pVM, &Desc);
    PX86DESC pShwDescr = &pVM->selm.s.paGdtRC[iGDTEntry];
    //Log(("O: base=%08X limit=%08X attr=%04X\n", X86DESC_BASE(*pShwDescr)), X86DESC_LIMIT(*pShwDescr), (pShwDescr->au32[1] >> 8) & 0xFFFF ));
    //Log(("N: base=%08X limit=%08X attr=%04X\n", X86DESC_BASE(Desc)), X86DESC_LIMIT(Desc), (Desc.au32[1] >> 8) & 0xFFFF ));
    *pShwDescr = Desc;

    /*
     * Detect and mark stale registers.
     */
    VBOXSTRICTRC rcStrict = VINF_SUCCESS;
    PCPUMSELREG  paSReg   = CPUMCTX_FIRST_SREG(pCtx);
    for (unsigned iSReg = 0; iSReg <= X86_SREG_COUNT; iSReg++)
    {
        if (Sel == (paSReg[iSReg].Sel & X86_SEL_MASK_OFF_RPL))
        {
            if (CPUMSELREG_ARE_HIDDEN_PARTS_VALID(pVCpu, &paSReg[iSReg]))
            {
                if (selmIsSRegStale32(&paSReg[iSReg], &Desc, iSReg))
                {
                    Log(("GDT write to selector in %s register %04X (now stale)\n", g_aszSRegNms[iSReg], paSReg[iSReg].Sel));
                    paSReg[iSReg].fFlags |= CPUMSELREG_FLAGS_STALE;
                    VMCPU_FF_SET(pVCpu, VMCPU_FF_TO_R3); /* paranoia */
                    /* rcStrict = VINF_EM_RESCHEDULE_REM; - bad idea if we're in a patch. */
                    rcStrict = VINF_EM_RAW_EMULATE_INSTR_GDT_FAULT;
                }
                else if (paSReg[iSReg].fFlags & CPUMSELREG_FLAGS_STALE)
                {
                    Log(("GDT write to selector in %s register %04X (no longer stale)\n", g_aszSRegNms[iSReg], paSReg[iSReg].Sel));
                    paSReg[iSReg].fFlags &= ~CPUMSELREG_FLAGS_STALE;
                }
                else
                    Log(("GDT write to selector in %s register %04X (no important change)\n", g_aszSRegNms[iSReg], paSReg[iSReg].Sel));
            }
            else
                Log(("GDT write to selector in %s register %04X (out of sync)\n", paSReg[iSReg].Sel));
        }
    }

    /** @todo Detect stale LDTR as well? */

    return rcStrict;
}