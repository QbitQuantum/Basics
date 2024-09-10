Error
IRExecutionUnit::DisassembleFunction (Stream &stream,
                                      lldb::ProcessSP &process_wp)
{
    Log *log(lldb_private::GetLogIfAllCategoriesSet (LIBLLDB_LOG_EXPRESSIONS));

    ExecutionContext exe_ctx(process_wp);

    Error ret;

    ret.Clear();

    lldb::addr_t func_local_addr = LLDB_INVALID_ADDRESS;
    lldb::addr_t func_remote_addr = LLDB_INVALID_ADDRESS;

    for (JittedFunction &function : m_jitted_functions)
    {
        if (strstr(function.m_name.c_str(), m_name.AsCString()))
        {
            func_local_addr = function.m_local_addr;
            func_remote_addr = function.m_remote_addr;
        }
    }

    if (func_local_addr == LLDB_INVALID_ADDRESS)
    {
        ret.SetErrorToGenericError();
        ret.SetErrorStringWithFormat("Couldn't find function %s for disassembly", m_name.AsCString());
        return ret;
    }

    if (log)
        log->Printf("Found function, has local address 0x%" PRIx64 " and remote address 0x%" PRIx64, (uint64_t)func_local_addr, (uint64_t)func_remote_addr);

    std::pair <lldb::addr_t, lldb::addr_t> func_range;

    func_range = GetRemoteRangeForLocal(func_local_addr);

    if (func_range.first == 0 && func_range.second == 0)
    {
        ret.SetErrorToGenericError();
        ret.SetErrorStringWithFormat("Couldn't find code range for function %s", m_name.AsCString());
        return ret;
    }

    if (log)
        log->Printf("Function's code range is [0x%" PRIx64 "+0x%" PRIx64 "]", func_range.first, func_range.second);

    Target *target = exe_ctx.GetTargetPtr();
    if (!target)
    {
        ret.SetErrorToGenericError();
        ret.SetErrorString("Couldn't find the target");
        return ret;
    }

    lldb::DataBufferSP buffer_sp(new DataBufferHeap(func_range.second, 0));

    Process *process = exe_ctx.GetProcessPtr();
    Error err;
    process->ReadMemory(func_remote_addr, buffer_sp->GetBytes(), buffer_sp->GetByteSize(), err);

    if (!err.Success())
    {
        ret.SetErrorToGenericError();
        ret.SetErrorStringWithFormat("Couldn't read from process: %s", err.AsCString("unknown error"));
        return ret;
    }

    ArchSpec arch(target->GetArchitecture());

    const char *plugin_name = NULL;
    const char *flavor_string = NULL;
    lldb::DisassemblerSP disassembler_sp = Disassembler::FindPlugin(arch, flavor_string, plugin_name);

    if (!disassembler_sp)
    {
        ret.SetErrorToGenericError();
        ret.SetErrorStringWithFormat("Unable to find disassembler plug-in for %s architecture.", arch.GetArchitectureName());
        return ret;
    }

    if (!process)
    {
        ret.SetErrorToGenericError();
        ret.SetErrorString("Couldn't find the process");
        return ret;
    }

    DataExtractor extractor(buffer_sp,
                            process->GetByteOrder(),
                            target->GetArchitecture().GetAddressByteSize());

    if (log)
    {
        log->Printf("Function data has contents:");
        extractor.PutToLog (log,
                            0,
                            extractor.GetByteSize(),
                            func_remote_addr,
                            16,
                            DataExtractor::TypeUInt8);
    }

    disassembler_sp->DecodeInstructions (Address (func_remote_addr), extractor, 0, UINT32_MAX, false, false);

    InstructionList &instruction_list = disassembler_sp->GetInstructionList();
    const uint32_t max_opcode_byte_size = instruction_list.GetMaxOpcocdeByteSize();
    const char *disassemble_format = "${addr-file-or-load}: ";
    if (exe_ctx.HasTargetScope())
    {
        disassemble_format = exe_ctx.GetTargetRef().GetDebugger().GetDisassemblyFormat();
    }

    for (size_t instruction_index = 0, num_instructions = instruction_list.GetSize();
         instruction_index < num_instructions;
         ++instruction_index)
    {
        Instruction *instruction = instruction_list.GetInstructionAtIndex(instruction_index).get();
        instruction->Dump (&stream,
                           max_opcode_byte_size,
                           true,
                           true,
                           &exe_ctx,
                           NULL,
                           NULL,
                           disassemble_format);
        stream.PutChar('\n');
    }
    // FIXME: The DisassemblerLLVMC has a reference cycle and won't go away if it has any active instructions.
    // I'll fix that but for now, just clear the list and it will go away nicely.
    disassembler_sp->GetInstructionList().Clear();
    return ret;
}