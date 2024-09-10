/* called from int1 handler, returns true if a hardware breakpoint was triggered in the current task */
int hbpCheck(THREAD *tThread)
{
    CONTEXT ctx;
    if (!tThread)
        return 0;
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    GetThreadContext(tThread->hThread, &ctx);
    if (ctx.Dr6 &15)
    {
        int i;
        for (i = 0; i < 4; i++)
            if (ctx.Dr6 &(1 << i))
                ExtendedMessageBox("Hardware Breakpoint", MB_SYSTEMMODAL |
                    MB_SETFOREGROUND, "Hardware breakpoint for %s triggered",
                    hdwebp[i].name);
    }
    return ctx.Dr6 &15;
}