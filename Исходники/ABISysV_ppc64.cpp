ValueObjectSP ABISysV_ppc64::GetReturnValueObjectImpl(
    Thread &thread, CompilerType &return_compiler_type) const {
  ValueObjectSP return_valobj_sp;

  if (!return_compiler_type)
    return return_valobj_sp;

  ExecutionContext exe_ctx(thread.shared_from_this());
  return_valobj_sp = GetReturnValueObjectSimple(thread, return_compiler_type);
  if (return_valobj_sp)
    return return_valobj_sp;

  RegisterContextSP reg_ctx_sp = thread.GetRegisterContext();
  if (!reg_ctx_sp)
    return return_valobj_sp;

  const size_t bit_width = return_compiler_type.GetBitSize(&thread);
  if (return_compiler_type.IsAggregateType()) {
    Target *target = exe_ctx.GetTargetPtr();
    bool is_memory = true;
    if (bit_width <= 128) {
      ByteOrder target_byte_order = target->GetArchitecture().GetByteOrder();
      DataBufferSP data_sp(new DataBufferHeap(16, 0));
      DataExtractor return_ext(data_sp, target_byte_order,
                               target->GetArchitecture().GetAddressByteSize());

      const RegisterInfo *r3_info = reg_ctx_sp->GetRegisterInfoByName("r3", 0);
      const RegisterInfo *rdx_info =
          reg_ctx_sp->GetRegisterInfoByName("rdx", 0);

      RegisterValue r3_value, rdx_value;
      reg_ctx_sp->ReadRegister(r3_info, r3_value);
      reg_ctx_sp->ReadRegister(rdx_info, rdx_value);

      DataExtractor r3_data, rdx_data;

      r3_value.GetData(r3_data);
      rdx_value.GetData(rdx_data);

      uint32_t fp_bytes =
          0; // Tracks how much of the xmm registers we've consumed so far
      uint32_t integer_bytes =
          0; // Tracks how much of the r3/rds registers we've consumed so far

      const uint32_t num_children = return_compiler_type.GetNumFields();

      // Since we are in the small struct regime, assume we are not in memory.
      is_memory = false;

      for (uint32_t idx = 0; idx < num_children; idx++) {
        std::string name;
        uint64_t field_bit_offset = 0;
        bool is_signed;
        bool is_complex;
        uint32_t count;

        CompilerType field_compiler_type = return_compiler_type.GetFieldAtIndex(
            idx, name, &field_bit_offset, nullptr, nullptr);
        const size_t field_bit_width = field_compiler_type.GetBitSize(&thread);

        // If there are any unaligned fields, this is stored in memory.
        if (field_bit_offset % field_bit_width != 0) {
          is_memory = true;
          break;
        }

        uint32_t field_byte_width = field_bit_width / 8;
        uint32_t field_byte_offset = field_bit_offset / 8;

        DataExtractor *copy_from_extractor = nullptr;
        uint32_t copy_from_offset = 0;

        if (field_compiler_type.IsIntegerOrEnumerationType(is_signed) ||
            field_compiler_type.IsPointerType()) {
          if (integer_bytes < 8) {
            if (integer_bytes + field_byte_width <= 8) {
              // This is in RAX, copy from register to our result structure:
              copy_from_extractor = &r3_data;
              copy_from_offset = integer_bytes;
              integer_bytes += field_byte_width;
            } else {
              // The next field wouldn't fit in the remaining space, so we
              // pushed it to rdx.
              copy_from_extractor = &rdx_data;
              copy_from_offset = 0;
              integer_bytes = 8 + field_byte_width;
            }
          } else if (integer_bytes + field_byte_width <= 16) {
            copy_from_extractor = &rdx_data;
            copy_from_offset = integer_bytes - 8;
            integer_bytes += field_byte_width;
          } else {
            // The last field didn't fit.  I can't see how that would happen w/o
            // the overall size being
            // greater than 16 bytes.  For now, return a nullptr return value
            // object.
            return return_valobj_sp;
          }
        } else if (field_compiler_type.IsFloatingPointType(count, is_complex)) {
          // Structs with long doubles are always passed in memory.
          if (field_bit_width == 128) {
            is_memory = true;
            break;
          } else if (field_bit_width == 64) {
            copy_from_offset = 0;
            fp_bytes += field_byte_width;
          } else if (field_bit_width == 32) {
            // This one is kind of complicated.  If we are in an "eightbyte"
            // with another float, we'll
            // be stuffed into an xmm register with it.  If we are in an
            // "eightbyte" with one or more ints,
            // then we will be stuffed into the appropriate GPR with them.
            bool in_gpr;
            if (field_byte_offset % 8 == 0) {
              // We are at the beginning of one of the eightbytes, so check the
              // next element (if any)
              if (idx == num_children - 1)
                in_gpr = false;
              else {
                uint64_t next_field_bit_offset = 0;
                CompilerType next_field_compiler_type =
                    return_compiler_type.GetFieldAtIndex(idx + 1, name,
                                                         &next_field_bit_offset,
                                                         nullptr, nullptr);
                if (next_field_compiler_type.IsIntegerOrEnumerationType(
                        is_signed))
                  in_gpr = true;
                else {
                  copy_from_offset = 0;
                  in_gpr = false;
                }
              }
            } else if (field_byte_offset % 4 == 0) {
              // We are inside of an eightbyte, so see if the field before us is
              // floating point:
              // This could happen if somebody put padding in the structure.
              if (idx == 0)
                in_gpr = false;
              else {
                uint64_t prev_field_bit_offset = 0;
                CompilerType prev_field_compiler_type =
                    return_compiler_type.GetFieldAtIndex(idx - 1, name,
                                                         &prev_field_bit_offset,
                                                         nullptr, nullptr);
                if (prev_field_compiler_type.IsIntegerOrEnumerationType(
                        is_signed))
                  in_gpr = true;
                else {
                  copy_from_offset = 4;
                  in_gpr = false;
                }
              }
            } else {
              is_memory = true;
              continue;
            }

            // Okay, we've figured out whether we are in GPR or XMM, now figure
            // out which one.
            if (in_gpr) {
              if (integer_bytes < 8) {
                // This is in RAX, copy from register to our result structure:
                copy_from_extractor = &r3_data;
                copy_from_offset = integer_bytes;
                integer_bytes += field_byte_width;
              } else {
                copy_from_extractor = &rdx_data;
                copy_from_offset = integer_bytes - 8;
                integer_bytes += field_byte_width;
              }
            } else {
              fp_bytes += field_byte_width;
            }
          }
        }

        // These two tests are just sanity checks.  If I somehow get the
        // type calculation wrong above it is better to just return nothing
        // than to assert or crash.
        if (!copy_from_extractor)
          return return_valobj_sp;
        if (copy_from_offset + field_byte_width >
            copy_from_extractor->GetByteSize())
          return return_valobj_sp;

        copy_from_extractor->CopyByteOrderedData(
            copy_from_offset, field_byte_width,
            data_sp->GetBytes() + field_byte_offset, field_byte_width,
            target_byte_order);
      }

      if (!is_memory) {
        // The result is in our data buffer.  Let's make a variable object out
        // of it:
        return_valobj_sp = ValueObjectConstResult::Create(
            &thread, return_compiler_type, ConstString(""), return_ext);
      }
    }

    // FIXME: This is just taking a guess, r3 may very well no longer hold the
    // return storage location.
    // If we are going to do this right, when we make a new frame we should
    // check to see if it uses a memory
    // return, and if we are at the first instruction and if so stash away the
    // return location.  Then we would
    // only return the memory return value if we know it is valid.

    if (is_memory) {
      unsigned r3_id =
          reg_ctx_sp->GetRegisterInfoByName("r3", 0)->kinds[eRegisterKindLLDB];
      lldb::addr_t storage_addr =
          (uint64_t)thread.GetRegisterContext()->ReadRegisterAsUnsigned(r3_id,
                                                                        0);
      return_valobj_sp = ValueObjectMemory::Create(
          &thread, "", Address(storage_addr, nullptr), return_compiler_type);
    }
  }

  return return_valobj_sp;
}