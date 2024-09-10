void ContextOverride::OnPreExecute( PreExecuteEvent &event, bool firstTime )
{
    if (!firstTime) return;
    if (m_done) return;
    u32 entry = LxEmulator.Proc()->GetEntryPoint();
    if (event.Cpu->EIP != entry) return;

    CONTEXT ctx;
    RefProcess *refproc = LxEmulator.RefProc();
    m_pi = refproc->GetProcessInformation();
    m_event = refproc->GetDebugEvent();

    byte origByte = refproc->SetInt3(entry);
    ContinueDebugEvent(m_pi->dwProcessId, m_pi->dwThreadId, DBG_CONTINUE);
    while (WaitForDebugEvent(m_event, INFINITE)) {
        if (m_event->dwDebugEventCode == EXCEPTION_DEBUG_EVENT &&
            m_event->u.Exception.ExceptionRecord.ExceptionCode == STATUS_BREAKPOINT)
        {
            refproc->GetMainContext(&ctx, CONTEXT_CONTROL);
            ctx.Eip--;
            if (ctx.Eip != entry) {
                LxFatal("SyncDiff: Unexpected sync address %08x, should be %08x\n",
                    ctx.Eip, entry);
            }
            refproc->SetMainContext(&ctx);
            refproc->RestoreInt3(ctx.Eip, origByte);
            break;
        }
        ContinueDebugEvent(m_pi->dwProcessId, m_pi->dwThreadId, DBG_CONTINUE);
    }
    refproc->SetTF();

    LxInfo("Overriding Context..\n");
    OverrideContext(event.Cpu);
    m_done = true;
}