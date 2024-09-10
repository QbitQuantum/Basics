uint32_t
UnwindMacOSXFrameBackchain::DoGetFrameCount()
{
    if (m_cursors.empty())
    {
        ExecutionContext exe_ctx (m_thread.shared_from_this());
        Target *target = exe_ctx.GetTargetPtr();
        if (target)
        {
            const ArchSpec& target_arch = target->GetArchitecture ();
            // Frame zero should always be supplied by the thread...
            exe_ctx.SetFrameSP (m_thread.GetStackFrameAtIndex (0));
            
            if (target_arch.GetAddressByteSize() == 8)
                GetStackFrameData_x86_64 (exe_ctx);
            else
                GetStackFrameData_i386 (exe_ctx);
        }
    }
    return m_cursors.size();
}