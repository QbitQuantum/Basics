  void Materialize(lldb::StackFrameSP &frame_sp, IRMemoryMap &map,
                   lldb::addr_t process_address, Status &err) override {
    Log *log(lldb_private::GetLogIfAllCategoriesSet(LIBLLDB_LOG_EXPRESSIONS));

    const lldb::addr_t load_addr = process_address + m_offset;
    if (log) {
      log->Printf("EntityVariable::Materialize [address = 0x%" PRIx64
                  ", m_variable_sp = %s]",
                  (uint64_t)load_addr, m_variable_sp->GetName().AsCString());
    }

    ExecutionContextScope *scope = frame_sp.get();

    if (!scope)
      scope = map.GetBestExecutionContextScope();

    lldb::ValueObjectSP valobj_sp =
        ValueObjectVariable::Create(scope, m_variable_sp);

    if (!valobj_sp) {
      err.SetErrorStringWithFormat(
          "couldn't get a value object for variable %s",
          m_variable_sp->GetName().AsCString());
      return;
    }

    Status valobj_error = valobj_sp->GetError();

    if (valobj_error.Fail()) {
      err.SetErrorStringWithFormat("couldn't get the value of variable %s: %s",
                                   m_variable_sp->GetName().AsCString(),
                                   valobj_error.AsCString());
      return;
    }

    if (m_is_reference) {
      DataExtractor valobj_extractor;
      Status extract_error;
      valobj_sp->GetData(valobj_extractor, extract_error);

      if (!extract_error.Success()) {
        err.SetErrorStringWithFormat(
            "couldn't read contents of reference variable %s: %s",
            m_variable_sp->GetName().AsCString(), extract_error.AsCString());
        return;
      }

      lldb::offset_t offset = 0;
      lldb::addr_t reference_addr = valobj_extractor.GetAddress(&offset);

      Status write_error;
      map.WritePointerToMemory(load_addr, reference_addr, write_error);

      if (!write_error.Success()) {
        err.SetErrorStringWithFormat("couldn't write the contents of reference "
                                     "variable %s to memory: %s",
                                     m_variable_sp->GetName().AsCString(),
                                     write_error.AsCString());
        return;
      }
    } else {
      AddressType address_type = eAddressTypeInvalid;
      const bool scalar_is_load_address = false;
      lldb::addr_t addr_of_valobj =
          valobj_sp->GetAddressOf(scalar_is_load_address, &address_type);
      if (addr_of_valobj != LLDB_INVALID_ADDRESS) {
        Status write_error;
        map.WritePointerToMemory(load_addr, addr_of_valobj, write_error);

        if (!write_error.Success()) {
          err.SetErrorStringWithFormat(
              "couldn't write the address of variable %s to memory: %s",
              m_variable_sp->GetName().AsCString(), write_error.AsCString());
          return;
        }
      } else {
        DataExtractor data;
        Status extract_error;
        valobj_sp->GetData(data, extract_error);
        if (!extract_error.Success()) {
          err.SetErrorStringWithFormat("couldn't get the value of %s: %s",
                                       m_variable_sp->GetName().AsCString(),
                                       extract_error.AsCString());
          return;
        }

        if (m_temporary_allocation != LLDB_INVALID_ADDRESS) {
          err.SetErrorStringWithFormat(
              "trying to create a temporary region for %s but one exists",
              m_variable_sp->GetName().AsCString());
          return;
        }

        if (data.GetByteSize() < m_variable_sp->GetType()->GetByteSize()) {
          if (data.GetByteSize() == 0 &&
              m_variable_sp->LocationExpression().IsValid() == false) {
            err.SetErrorStringWithFormat("the variable '%s' has no location, "
                                         "it may have been optimized out",
                                         m_variable_sp->GetName().AsCString());
          } else {
            err.SetErrorStringWithFormat(
                "size of variable %s (%" PRIu64
                ") is larger than the ValueObject's size (%" PRIu64 ")",
                m_variable_sp->GetName().AsCString(),
                m_variable_sp->GetType()->GetByteSize(), data.GetByteSize());
          }
          return;
        }

        size_t bit_align =
            m_variable_sp->GetType()->GetLayoutCompilerType().GetTypeBitAlign();
        size_t byte_align = (bit_align + 7) / 8;

        if (!byte_align)
          byte_align = 1;

        Status alloc_error;
        const bool zero_memory = false;

        m_temporary_allocation = map.Malloc(
            data.GetByteSize(), byte_align,
            lldb::ePermissionsReadable | lldb::ePermissionsWritable,
            IRMemoryMap::eAllocationPolicyMirror, zero_memory, alloc_error);

        m_temporary_allocation_size = data.GetByteSize();

        m_original_data.reset(
            new DataBufferHeap(data.GetDataStart(), data.GetByteSize()));

        if (!alloc_error.Success()) {
          err.SetErrorStringWithFormat(
              "couldn't allocate a temporary region for %s: %s",
              m_variable_sp->GetName().AsCString(), alloc_error.AsCString());
          return;
        }

        Status write_error;

        map.WriteMemory(m_temporary_allocation, data.GetDataStart(),
                        data.GetByteSize(), write_error);

        if (!write_error.Success()) {
          err.SetErrorStringWithFormat(
              "couldn't write to the temporary region for %s: %s",
              m_variable_sp->GetName().AsCString(), write_error.AsCString());
          return;
        }

        Status pointer_write_error;

        map.WritePointerToMemory(load_addr, m_temporary_allocation,
                                 pointer_write_error);

        if (!pointer_write_error.Success()) {
          err.SetErrorStringWithFormat(
              "couldn't write the address of the temporary region for %s: %s",
              m_variable_sp->GetName().AsCString(),
              pointer_write_error.AsCString());
        }
      }
    }
  }