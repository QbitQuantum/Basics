Error
Value::GetValueAsData (ExecutionContext *exe_ctx,
                       DataExtractor &data,
                       uint32_t data_offset,
                       Module *module)
{
    data.Clear();

    Error error;
    lldb::addr_t address = LLDB_INVALID_ADDRESS;
    AddressType address_type = eAddressTypeFile;
    Address file_so_addr;
    const CompilerType &ast_type = GetCompilerType();
    switch (m_value_type)
    {
    case eValueTypeVector:
        if (ast_type.IsValid())
            data.SetAddressByteSize (ast_type.GetPointerByteSize());
        else
            data.SetAddressByteSize(sizeof(void *));
        data.SetData(m_vector.bytes, m_vector.length, m_vector.byte_order);
        break;

    case eValueTypeScalar:
        {
            data.SetByteOrder (endian::InlHostByteOrder());
            if (ast_type.IsValid())
                data.SetAddressByteSize (ast_type.GetPointerByteSize());
            else
                data.SetAddressByteSize(sizeof(void *));

            uint32_t limit_byte_size = UINT32_MAX;
            
            if (ast_type.IsValid() && ast_type.IsScalarType())
            {
                uint64_t type_encoding_count = 0;
                lldb::Encoding type_encoding = ast_type.GetEncoding(type_encoding_count);
                
                if (type_encoding == eEncodingUint || type_encoding == eEncodingSint)
                    limit_byte_size = ast_type.GetByteSize(exe_ctx ? exe_ctx->GetBestExecutionContextScope() : nullptr);
            }
            
            if (m_value.GetData (data, limit_byte_size))
                return error;   // Success;
            
            error.SetErrorStringWithFormat("extracting data from value failed");
            break;
        }
    case eValueTypeLoadAddress:
        if (exe_ctx == NULL)
        {
            error.SetErrorString ("can't read load address (no execution context)");
        }
        else 
        {
            Process *process = exe_ctx->GetProcessPtr();
            if (process == NULL || !process->IsAlive())
            {
                Target *target = exe_ctx->GetTargetPtr();
                if (target)
                {
                    // Allow expressions to run and evaluate things when the target
                    // has memory sections loaded. This allows you to use "target modules load"
                    // to load your executable and any shared libraries, then execute
                    // commands where you can look at types in data sections.
                    const SectionLoadList &target_sections = target->GetSectionLoadList();
                    if (!target_sections.IsEmpty())
                    {
                        address = m_value.ULongLong(LLDB_INVALID_ADDRESS);
                        if (target_sections.ResolveLoadAddress(address, file_so_addr))
                        {
                            address_type = eAddressTypeLoad;
                            data.SetByteOrder(target->GetArchitecture().GetByteOrder());
                            data.SetAddressByteSize(target->GetArchitecture().GetAddressByteSize());
                        }
                        else
                            address = LLDB_INVALID_ADDRESS;
                    }
//                    else
//                    {
//                        ModuleSP exe_module_sp (target->GetExecutableModule());
//                        if (exe_module_sp)
//                        {
//                            address = m_value.ULongLong(LLDB_INVALID_ADDRESS);
//                            if (address != LLDB_INVALID_ADDRESS)
//                            {
//                                if (exe_module_sp->ResolveFileAddress(address, file_so_addr))
//                                {
//                                    data.SetByteOrder(target->GetArchitecture().GetByteOrder());
//                                    data.SetAddressByteSize(target->GetArchitecture().GetAddressByteSize());
//                                    address_type = eAddressTypeFile;
//                                }
//                                else
//                                {
//                                    address = LLDB_INVALID_ADDRESS;
//                                }
//                            }
//                        }
//                    }
                }
                else
                {
                    error.SetErrorString ("can't read load address (invalid process)");
                }
            }
            else
            {
                address = m_value.ULongLong(LLDB_INVALID_ADDRESS);
                address_type = eAddressTypeLoad;
                data.SetByteOrder(process->GetTarget().GetArchitecture().GetByteOrder());
                data.SetAddressByteSize(process->GetTarget().GetArchitecture().GetAddressByteSize());
            }
        }
        break;

    case eValueTypeFileAddress:
        if (exe_ctx == NULL)
        {
            error.SetErrorString ("can't read file address (no execution context)");
        }
        else if (exe_ctx->GetTargetPtr() == NULL)
        {
            error.SetErrorString ("can't read file address (invalid target)");
        }
        else
        {
            address = m_value.ULongLong(LLDB_INVALID_ADDRESS);
            if (address == LLDB_INVALID_ADDRESS)
            {
                error.SetErrorString ("invalid file address");
            }
            else
            {
                if (module == NULL)
                {
                    // The only thing we can currently lock down to a module so that
                    // we can resolve a file address, is a variable.
                    Variable *variable = GetVariable();
                    if (variable)
                    {
                        SymbolContext var_sc;
                        variable->CalculateSymbolContext(&var_sc);
                        module = var_sc.module_sp.get();
                    }
                }
                
                if (module)
                {
                    bool resolved = false;
                    ObjectFile *objfile = module->GetObjectFile();
                    if (objfile)
                    {
                        Address so_addr(address, objfile->GetSectionList());
                        addr_t load_address = so_addr.GetLoadAddress (exe_ctx->GetTargetPtr());
                        bool process_launched_and_stopped = exe_ctx->GetProcessPtr()
                            ? StateIsStoppedState(exe_ctx->GetProcessPtr()->GetState(), true /* must_exist */)
                            : false;
                        // Don't use the load address if the process has exited.
                        if (load_address != LLDB_INVALID_ADDRESS && process_launched_and_stopped)
                        {
                            resolved = true;
                            address = load_address;
                            address_type = eAddressTypeLoad;
                            data.SetByteOrder(exe_ctx->GetTargetRef().GetArchitecture().GetByteOrder());
                            data.SetAddressByteSize(exe_ctx->GetTargetRef().GetArchitecture().GetAddressByteSize());
                        }
                        else
                        {
                            if (so_addr.IsSectionOffset())
                            {
                                resolved = true;
                                file_so_addr = so_addr;
                                data.SetByteOrder(objfile->GetByteOrder());
                                data.SetAddressByteSize(objfile->GetAddressByteSize());
                            }
                        }
                    }
                    if (!resolved)
                    {
                        Variable *variable = GetVariable();
                        
                        if (module)
                        {
                            if (variable)
                                error.SetErrorStringWithFormat ("unable to resolve the module for file address 0x%" PRIx64 " for variable '%s' in %s",
                                                                address, 
                                                                variable->GetName().AsCString(""),
                                                                module->GetFileSpec().GetPath().c_str());
                            else
                                error.SetErrorStringWithFormat ("unable to resolve the module for file address 0x%" PRIx64 " in %s",
                                                                address, 
                                                                module->GetFileSpec().GetPath().c_str());
                        }
                        else
                        {
                            if (variable)
                                error.SetErrorStringWithFormat ("unable to resolve the module for file address 0x%" PRIx64 " for variable '%s'",
                                                                address, 
                                                                variable->GetName().AsCString(""));
                            else
                                error.SetErrorStringWithFormat ("unable to resolve the module for file address 0x%" PRIx64, address);
                        }
                    }
                }
                else
                {
                    // Can't convert a file address to anything valid without more
                    // context (which Module it came from)
                    error.SetErrorString ("can't read memory from file address without more context");
                }
            }
        }
        break;

    case eValueTypeHostAddress:
        address = m_value.ULongLong(LLDB_INVALID_ADDRESS);
        address_type = eAddressTypeHost;
        if (exe_ctx)
        {
            Target *target = exe_ctx->GetTargetPtr();
            if (target)
            {
                data.SetByteOrder(target->GetArchitecture().GetByteOrder());
                data.SetAddressByteSize(target->GetArchitecture().GetAddressByteSize());
                break;
            }
        }
        // fallback to host settings
        data.SetByteOrder(endian::InlHostByteOrder());
        data.SetAddressByteSize(sizeof(void *));
        break;
    }

    // Bail if we encountered any errors
    if (error.Fail())
        return error;

    if (address == LLDB_INVALID_ADDRESS)
    {
        error.SetErrorStringWithFormat ("invalid %s address", address_type == eAddressTypeHost ? "host" : "load");
        return error;
    }

    // If we got here, we need to read the value from memory
    size_t byte_size = GetValueByteSize (&error, exe_ctx);

    // Bail if we encountered any errors getting the byte size
    if (error.Fail())
        return error;

    // Make sure we have enough room within "data", and if we don't make
    // something large enough that does
    if (!data.ValidOffsetForDataOfSize (data_offset, byte_size))
    {
        DataBufferSP data_sp(new DataBufferHeap (data_offset + byte_size, '\0'));
        data.SetData(data_sp);
    }

    uint8_t* dst = const_cast<uint8_t*>(data.PeekData (data_offset, byte_size));
    if (dst != NULL)
    {
        if (address_type == eAddressTypeHost)
        {
            // The address is an address in this process, so just copy it.
            if (address == 0)
            {
                error.SetErrorStringWithFormat("trying to read from host address of 0.");
                return error;
            }
            memcpy (dst, (uint8_t*)NULL + address, byte_size);
        }
        else if ((address_type == eAddressTypeLoad) || (address_type == eAddressTypeFile))
        {
            if (file_so_addr.IsValid())
            {
                // We have a file address that we were able to translate into a
                // section offset address so we might be able to read this from
                // the object files if we don't have a live process. Lets always
                // try and read from the process if we have one though since we
                // want to read the actual value by setting "prefer_file_cache"
                // to false. 
                const bool prefer_file_cache = false;
                if (exe_ctx->GetTargetRef().ReadMemory(file_so_addr, prefer_file_cache, dst, byte_size, error) != byte_size)
                {
                    error.SetErrorStringWithFormat("read memory from 0x%" PRIx64 " failed", (uint64_t)address);
                }
            }
            else
            {
                // The execution context might have a NULL process, but it
                // might have a valid process in the exe_ctx->target, so use
                // the ExecutionContext::GetProcess accessor to ensure we
                // get the process if there is one.
                Process *process = exe_ctx->GetProcessPtr();

                if (process)
                {
                    const size_t bytes_read = process->ReadMemory(address, dst, byte_size, error);
                    if (bytes_read != byte_size)
                        error.SetErrorStringWithFormat("read memory from 0x%" PRIx64 " failed (%u of %u bytes read)",
                                                       (uint64_t)address, 
                                                       (uint32_t)bytes_read, 
                                                       (uint32_t)byte_size);
                }
                else
                {
                    error.SetErrorStringWithFormat("read memory from 0x%" PRIx64 " failed (invalid process)", (uint64_t)address);
                }
            }
        }
        else
        {
            error.SetErrorStringWithFormat ("unsupported AddressType value (%i)", address_type);
        }
    }
    else
    {
        error.SetErrorStringWithFormat ("out of memory");
    }

    return error;
}