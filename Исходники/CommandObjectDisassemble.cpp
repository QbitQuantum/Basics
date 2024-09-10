bool
CommandObjectDisassemble::Execute
(
    CommandInterpreter &interpreter,
    Args& command,
    CommandReturnObject &result
)
{
    Target *target = interpreter.GetDebugger().GetCurrentTarget().get();
    if (target == NULL)
    {
        result.AppendError ("invalid target, set executable file using 'file' command");
        result.SetStatus (eReturnStatusFailed);
        return false;
    }

    ArchSpec arch(target->GetArchitecture());
    if (!arch.IsValid())
    {
        result.AppendError ("target needs valid architecure in order to be able to disassemble");
        result.SetStatus (eReturnStatusFailed);
        return false;
    }

    Disassembler *disassembler = Disassembler::FindPlugin(arch);

    if (disassembler == NULL)
    {
        result.AppendErrorWithFormat ("Unable to find Disassembler plug-in for %s architecture.\n", arch.AsCString());
        result.SetStatus (eReturnStatusFailed);
        return false;
    }

    result.SetStatus (eReturnStatusSuccessFinishResult);

    if (command.GetArgumentCount() != 0)
    {
        result.AppendErrorWithFormat ("\"disassemble\" doesn't take any arguments.\n");
        result.SetStatus (eReturnStatusFailed);
        return false;
    }
    ExecutionContext exe_ctx(interpreter.GetDebugger().GetExecutionContext());

    if (m_options.show_mixed && m_options.num_lines_context == 0)
        m_options.num_lines_context = 3;

    if (!m_options.m_func_name.empty())
    {
        ConstString name(m_options.m_func_name.c_str());
        
        if (Disassembler::Disassemble (interpreter.GetDebugger(), 
                                       arch,
                                       exe_ctx,
                                       name,
                                       NULL,    // Module *
                                       m_options.show_mixed ? m_options.num_lines_context : 0,
                                       m_options.show_bytes,
                                       result.GetOutputStream()))
        {
            result.SetStatus (eReturnStatusSuccessFinishResult);
        }
        else
        {
            result.AppendErrorWithFormat ("Unable to find symbol with name '%s'.\n", name.GetCString());
            result.SetStatus (eReturnStatusFailed);
        }
    } 
    else
    {
        AddressRange range;
        if (m_options.m_start_addr != LLDB_INVALID_ADDRESS)
        {
            range.GetBaseAddress().SetOffset (m_options.m_start_addr);
            if (m_options.m_end_addr != LLDB_INVALID_ADDRESS)
            {
                if (m_options.m_end_addr < m_options.m_start_addr)
                {
                    result.AppendErrorWithFormat ("End address before start address.\n");
                    result.SetStatus (eReturnStatusFailed);
                    return false;            
                }
                range.SetByteSize (m_options.m_end_addr - m_options.m_start_addr);
            }
            else
                range.SetByteSize (DEFAULT_DISASM_BYTE_SIZE);
        } 
        else
        {
            if (exe_ctx.frame)
            {
                SymbolContext sc(exe_ctx.frame->GetSymbolContext(eSymbolContextFunction | eSymbolContextSymbol));
                if (sc.function)
                    range = sc.function->GetAddressRange();
                else if (sc.symbol && sc.symbol->GetAddressRangePtr())
                    range = *sc.symbol->GetAddressRangePtr();
                else
                    range.GetBaseAddress() = exe_ctx.frame->GetPC();
            }
            else
            {
                result.AppendError ("invalid frame");
                result.SetStatus (eReturnStatusFailed);
                return false;
            }
        }
        if (range.GetByteSize() == 0)
            range.SetByteSize(DEFAULT_DISASM_BYTE_SIZE);

        if (Disassembler::Disassemble (interpreter.GetDebugger(), 
                                       arch,
                                       exe_ctx,
                                       range,
                                       m_options.show_mixed ? m_options.num_lines_context : 0,
                                       m_options.show_bytes,
                                       result.GetOutputStream()))
        {
            result.SetStatus (eReturnStatusSuccessFinishResult);
        }
        else
        {
            result.AppendErrorWithFormat ("Failed to disassemble memory at 0x%8.8llx.\n", m_options.m_start_addr);
            result.SetStatus (eReturnStatusFailed);            
        }
    }

    return result.Succeeded();
}