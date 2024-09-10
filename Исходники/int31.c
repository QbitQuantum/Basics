/* (see dosmem.c, function DOSMEM_InitDPMI) */
static void StartPM( CONTEXT86 *context )
{
    UINT16 cs, ss, ds, es;
    CONTEXT86 pm_ctx;
    DWORD psp_ofs = (DWORD)(DOSVM_psp<<4);
    PDB16 *psp = (PDB16 *)psp_ofs;
    HANDLE16 env_seg = psp->environment;
    unsigned char selflags = WINE_LDT_FLAGS_DATA;

    RESET_CFLAG(context);
    dpmi_flag = AX_reg(context);
/* our mode switch wrapper have placed the desired CS into DX */
    cs = alloc_pm_selector( context->Edx, WINE_LDT_FLAGS_CODE );
/* due to a flaw in some CPUs (at least mine), it is best to mark stack segments as 32-bit if they
   can be used in 32-bit code. Otherwise, these CPUs may not set the high word of esp during a
   ring transition (from kernel code) to the 16-bit stack, and this causes trouble if executing
   32-bit code using this stack. */
    if (dpmi_flag & 1) selflags |= WINE_LDT_FLAGS_32BIT;
    ss = alloc_pm_selector( context->SegSs, selflags );
/* do the same for the data segments, just in case */
    if (context->SegDs == context->SegSs) ds = ss;
    else ds = alloc_pm_selector( context->SegDs, selflags );
    es = alloc_pm_selector( DOSVM_psp, selflags );
/* convert environment pointer, as the spec says, but we're a bit lazy about the size here... */
    psp->environment = alloc_pm_selector( env_seg, WINE_LDT_FLAGS_DATA );

    pm_ctx = *context;
    pm_ctx.SegCs = DOSVM_dpmi_segments->dpmi_sel;
/* our mode switch wrapper expects the new CS in DX, and the new SS in AX */
    pm_ctx.Eax   = ss;
    pm_ctx.Edx   = cs;
    pm_ctx.SegDs = ds;
    pm_ctx.SegEs = es;
    pm_ctx.SegFs = wine_get_fs();
    pm_ctx.SegGs = wine_get_gs();
    pm_ctx.EFlags &= ~V86_FLAG;

    TRACE("DOS program is now entering %d-bit protected mode\n", 
          DOSVM_IsDos32() ? 32 : 16);

    __TRY 
    {
        WOWCallback16Ex( 0, WCB16_REGS, 0, NULL, (DWORD *)&pm_ctx );
    } 
    __EXCEPT(dpmi_exception_handler) 
    { 
    } 
    __ENDTRY

    TRACE( "Protected mode DOS program is terminating\n" );

    /*
     * FIXME: Instead of calling ExitThread, we should release all
     *        allocated protected mode resources and call MZ_Exit
     *        using real mode context. See DPMI specification.
     */
    ExitThread( DPMI_retval );

#if 0
    wine_ldt_free_entries( psp->environment, 1 );
    psp->environment = env_seg;
    wine_ldt_free_entries(es,1);
    if (ds != ss) wine_ldt_free_entries(ds,1);
    wine_ldt_free_entries(ss,1);
    wine_ldt_free_entries(cs,1);
#endif
}