void 
ThreadPlanAssemblyTracer::Log ()
{
    Stream *stream = GetLogStream ();
    
    if (!stream)
        return;
            
    RegisterContext *reg_ctx = m_thread.GetRegisterContext().get();
    
    lldb::addr_t pc = reg_ctx->GetPC();
    ProcessSP process_sp (m_thread.GetProcess());
    Address pc_addr;
    bool addr_valid = false;
    uint8_t buffer[16] = {0}; // Must be big enough for any single instruction
    addr_valid = process_sp->GetTarget().GetSectionLoadList().ResolveLoadAddress (pc, pc_addr);
    
    pc_addr.Dump(stream, &m_thread, Address::DumpStyleResolvedDescription, Address::DumpStyleModuleWithFileAddress);
    stream->PutCString (" ");
    
    Disassembler *disassembler = GetDisassembler();
    if (disassembler)
    {        
        Error err;
        process_sp->ReadMemory(pc, buffer, sizeof(buffer), err);
        
        if (err.Success())
        {
            DataExtractor extractor(buffer, sizeof(buffer), 
                                    process_sp->GetByteOrder(), 
                                    process_sp->GetAddressByteSize());
            
			bool data_from_file = false;
            if (addr_valid)
                disassembler->DecodeInstructions (pc_addr, extractor, 0, 1, false, data_from_file);
            else
                disassembler->DecodeInstructions (Address (pc), extractor, 0, 1, false, data_from_file);
            
            InstructionList &instruction_list = disassembler->GetInstructionList();
            const uint32_t max_opcode_byte_size = instruction_list.GetMaxOpcocdeByteSize();

            if (instruction_list.GetSize())
            {
                const bool show_bytes = true;
                const bool show_address = true;
                Instruction *instruction = instruction_list.GetInstructionAtIndex(0).get();
                const FormatEntity::Entry *disassemble_format = m_thread.GetProcess()->GetTarget().GetDebugger().GetDisassemblyFormat();
                instruction->Dump (stream,
                                   max_opcode_byte_size,
                                   show_address,
                                   show_bytes,
                                   NULL,
                                   NULL,
                                   NULL,
                                   disassemble_format,
                                   0);
            }
        }
    }
    
    const ABI *abi = process_sp->GetABI().get();
    TypeFromUser intptr_type = GetIntPointerType();
    
    if (abi && intptr_type.IsValid())
    {
        ValueList value_list;
        const int num_args = 1;
        
        for (int arg_index = 0; arg_index < num_args; ++arg_index)
        {
            Value value;
            value.SetValueType (Value::eValueTypeScalar);
//            value.SetContext (Value::eContextTypeClangType, intptr_type.GetOpaqueQualType());
            value.SetClangType (intptr_type);
            value_list.PushValue (value);
        }
        
        if (abi->GetArgumentValues (m_thread, value_list))
        {                
            for (int arg_index = 0; arg_index < num_args; ++arg_index)
            {
                stream->Printf("\n\targ[%d]=%llx", arg_index, value_list.GetValueAtIndex(arg_index)->GetScalar().ULongLong());
                
                if (arg_index + 1 < num_args)
                    stream->PutCString (", ");
            }
        }
    }
    
    
    RegisterValue reg_value;
    for (uint32_t reg_num = 0, num_registers = reg_ctx->GetRegisterCount();
         reg_num < num_registers;
         ++reg_num)
    {
        const RegisterInfo *reg_info = reg_ctx->GetRegisterInfoAtIndex(reg_num);
        if (reg_ctx->ReadRegister (reg_info, reg_value))
        {
            assert (reg_num < m_register_values.size());
            if (m_register_values[reg_num].GetType() == RegisterValue::eTypeInvalid || 
                reg_value != m_register_values[reg_num])
            {
                if (reg_value.GetType() != RegisterValue::eTypeInvalid)
                {
                    stream->PutCString ("\n\t");
                    reg_value.Dump(stream, reg_info, true, false, eFormatDefault);
                }
            }
            m_register_values[reg_num] = reg_value;
        }
    }
    stream->EOL();
    stream->Flush();
}