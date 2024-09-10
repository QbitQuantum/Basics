SBInstructionList
SBFunction::GetInstructions (SBTarget target)
{
    SBInstructionList sb_instructions;
    if (m_opaque_ptr)
    {
        Mutex::Locker api_locker;
        ExecutionContext exe_ctx;
        if (target.IsValid())
        {
            api_locker.Reset (target->GetAPIMutex().GetMutex());
            target->CalculateExecutionContext (exe_ctx);
            exe_ctx.process = target->GetProcessSP().get();
        }
        Module *module = m_opaque_ptr->GetAddressRange().GetBaseAddress().GetModule();
        if (module)
        {
            sb_instructions.SetDisassembler (Disassembler::DisassembleRange (module->GetArchitecture(),
                                                                             exe_ctx,
                                                                             m_opaque_ptr->GetAddressRange()));
        }
    }
    return sb_instructions;
}