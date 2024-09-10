bool Address::Dump(Stream *s, ExecutionContextScope *exe_scope, DumpStyle style,
                   DumpStyle fallback_style, uint32_t addr_size) const {
  // If the section was nullptr, only load address is going to work unless we
  // are
  // trying to deref a pointer
  SectionSP section_sp(GetSection());
  if (!section_sp && style != DumpStyleResolvedPointerDescription)
    style = DumpStyleLoadAddress;

  ExecutionContext exe_ctx(exe_scope);
  Target *target = exe_ctx.GetTargetPtr();
  // If addr_byte_size is UINT32_MAX, then determine the correct address
  // byte size for the process or default to the size of addr_t
  if (addr_size == UINT32_MAX) {
    if (target)
      addr_size = target->GetArchitecture().GetAddressByteSize();
    else
      addr_size = sizeof(addr_t);
  }

  Address so_addr;
  switch (style) {
  case DumpStyleInvalid:
    return false;

  case DumpStyleSectionNameOffset:
    if (section_sp) {
      section_sp->DumpName(s);
      s->Printf(" + %" PRIu64, m_offset);
    } else {
      s->Address(m_offset, addr_size);
    }
    break;

  case DumpStyleSectionPointerOffset:
    s->Printf("(Section *)%p + ", static_cast<void *>(section_sp.get()));
    s->Address(m_offset, addr_size);
    break;

  case DumpStyleModuleWithFileAddress:
    if (section_sp) {
      ModuleSP module_sp = section_sp->GetModule();
      if (module_sp)
        s->Printf("%s[", module_sp->GetFileSpec().GetFilename().AsCString(
                             "<Unknown>"));
      else
        s->Printf("%s[", "<Unknown>");
    }
    LLVM_FALLTHROUGH;
  case DumpStyleFileAddress: {
    addr_t file_addr = GetFileAddress();
    if (file_addr == LLDB_INVALID_ADDRESS) {
      if (fallback_style != DumpStyleInvalid)
        return Dump(s, exe_scope, fallback_style, DumpStyleInvalid, addr_size);
      return false;
    }
    s->Address(file_addr, addr_size);
    if (style == DumpStyleModuleWithFileAddress && section_sp)
      s->PutChar(']');
  } break;

  case DumpStyleLoadAddress: {
    addr_t load_addr = GetLoadAddress(target);

    /*
     * MIPS:
     * Display address in compressed form for MIPS16 or microMIPS
     * if the address belongs to eAddressClassCodeAlternateISA.
    */
    if (target) {
      const llvm::Triple::ArchType llvm_arch =
          target->GetArchitecture().GetMachine();
      if (llvm_arch == llvm::Triple::mips ||
          llvm_arch == llvm::Triple::mipsel ||
          llvm_arch == llvm::Triple::mips64 ||
          llvm_arch == llvm::Triple::mips64el)
        load_addr = GetCallableLoadAddress(target);
    }

    if (load_addr == LLDB_INVALID_ADDRESS) {
      if (fallback_style != DumpStyleInvalid)
        return Dump(s, exe_scope, fallback_style, DumpStyleInvalid, addr_size);
      return false;
    }
    s->Address(load_addr, addr_size);
  } break;

  case DumpStyleResolvedDescription:
  case DumpStyleResolvedDescriptionNoModule:
  case DumpStyleResolvedDescriptionNoFunctionArguments:
  case DumpStyleNoFunctionName:
    if (IsSectionOffset()) {
      uint32_t pointer_size = 4;
      ModuleSP module_sp(GetModule());
      if (target)
        pointer_size = target->GetArchitecture().GetAddressByteSize();
      else if (module_sp)
        pointer_size = module_sp->GetArchitecture().GetAddressByteSize();

      bool showed_info = false;
      if (section_sp) {
        SectionType sect_type = section_sp->GetType();
        switch (sect_type) {
        case eSectionTypeData:
          if (module_sp) {
            SymbolVendor *sym_vendor = module_sp->GetSymbolVendor();
            if (sym_vendor) {
              Symtab *symtab = sym_vendor->GetSymtab();
              if (symtab) {
                const addr_t file_Addr = GetFileAddress();
                Symbol *symbol =
                    symtab->FindSymbolContainingFileAddress(file_Addr);
                if (symbol) {
                  const char *symbol_name = symbol->GetName().AsCString();
                  if (symbol_name) {
                    s->PutCString(symbol_name);
                    addr_t delta =
                        file_Addr - symbol->GetAddressRef().GetFileAddress();
                    if (delta)
                      s->Printf(" + %" PRIu64, delta);
                    showed_info = true;
                  }
                }
              }
            }
          }
          break;

        case eSectionTypeDataCString:
          // Read the C string from memory and display it
          showed_info = true;
          ReadCStringFromMemory(exe_scope, *this, s);
          break;

        case eSectionTypeDataCStringPointers:
          if (ReadAddress(exe_scope, *this, pointer_size, so_addr)) {
#if VERBOSE_OUTPUT
            s->PutCString("(char *)");
            so_addr.Dump(s, exe_scope, DumpStyleLoadAddress,
                         DumpStyleFileAddress);
            s->PutCString(": ");
#endif
            showed_info = true;
            ReadCStringFromMemory(exe_scope, so_addr, s);
          }
          break;

        case eSectionTypeDataObjCMessageRefs:
          if (ReadAddress(exe_scope, *this, pointer_size, so_addr)) {
            if (target && so_addr.IsSectionOffset()) {
              SymbolContext func_sc;
              target->GetImages().ResolveSymbolContextForAddress(
                  so_addr, eSymbolContextEverything, func_sc);
              if (func_sc.function != nullptr || func_sc.symbol != nullptr) {
                showed_info = true;
#if VERBOSE_OUTPUT
                s->PutCString("(objc_msgref *) -> { (func*)");
                so_addr.Dump(s, exe_scope, DumpStyleLoadAddress,
                             DumpStyleFileAddress);
#else
                s->PutCString("{ ");
#endif
                Address cstr_addr(*this);
                cstr_addr.SetOffset(cstr_addr.GetOffset() + pointer_size);
                func_sc.DumpStopContext(s, exe_scope, so_addr, true, true,
                                        false, true, true);
                if (ReadAddress(exe_scope, cstr_addr, pointer_size, so_addr)) {
#if VERBOSE_OUTPUT
                  s->PutCString("), (char *)");
                  so_addr.Dump(s, exe_scope, DumpStyleLoadAddress,
                               DumpStyleFileAddress);
                  s->PutCString(" (");
#else
                  s->PutCString(", ");
#endif
                  ReadCStringFromMemory(exe_scope, so_addr, s);
                }
#if VERBOSE_OUTPUT
                s->PutCString(") }");
#else
                s->PutCString(" }");
#endif
              }
            }
          }
          break;

        case eSectionTypeDataObjCCFStrings: {
          Address cfstring_data_addr(*this);
          cfstring_data_addr.SetOffset(cfstring_data_addr.GetOffset() +
                                       (2 * pointer_size));
          if (ReadAddress(exe_scope, cfstring_data_addr, pointer_size,
                          so_addr)) {
#if VERBOSE_OUTPUT
            s->PutCString("(CFString *) ");
            cfstring_data_addr.Dump(s, exe_scope, DumpStyleLoadAddress,
                                    DumpStyleFileAddress);
            s->PutCString(" -> @");
#else
            s->PutChar('@');
#endif
            if (so_addr.Dump(s, exe_scope, DumpStyleResolvedDescription))
              showed_info = true;
          }
        } break;

        case eSectionTypeData4:
          // Read the 4 byte data and display it
          showed_info = true;
          s->PutCString("(uint32_t) ");
          DumpUInt(exe_scope, *this, 4, s);
          break;

        case eSectionTypeData8:
          // Read the 8 byte data and display it
          showed_info = true;
          s->PutCString("(uint64_t) ");
          DumpUInt(exe_scope, *this, 8, s);
          break;

        case eSectionTypeData16:
          // Read the 16 byte data and display it
          showed_info = true;
          s->PutCString("(uint128_t) ");
          DumpUInt(exe_scope, *this, 16, s);
          break;

        case eSectionTypeDataPointers:
          // Read the pointer data and display it
          if (ReadAddress(exe_scope, *this, pointer_size, so_addr)) {
            s->PutCString("(void *)");
            so_addr.Dump(s, exe_scope, DumpStyleLoadAddress,
                         DumpStyleFileAddress);

            showed_info = true;
            if (so_addr.IsSectionOffset()) {
              SymbolContext pointer_sc;
              if (target) {
                target->GetImages().ResolveSymbolContextForAddress(
                    so_addr, eSymbolContextEverything, pointer_sc);
                if (pointer_sc.function != nullptr ||
                    pointer_sc.symbol != nullptr) {
                  s->PutCString(": ");
                  pointer_sc.DumpStopContext(s, exe_scope, so_addr, true, false,
                                             false, true, true);
                }
              }
            }
          }
          break;

        default:
          break;
        }
      }

      if (!showed_info) {
        if (module_sp) {
          SymbolContext sc;
          module_sp->ResolveSymbolContextForAddress(
              *this, eSymbolContextEverything, sc);
          if (sc.function || sc.symbol) {
            bool show_stop_context = true;
            const bool show_module = (style == DumpStyleResolvedDescription);
            const bool show_fullpaths = false;
            const bool show_inlined_frames = true;
            const bool show_function_arguments =
                (style != DumpStyleResolvedDescriptionNoFunctionArguments);
            const bool show_function_name = (style != DumpStyleNoFunctionName);
            if (sc.function == nullptr && sc.symbol != nullptr) {
              // If we have just a symbol make sure it is in the right section
              if (sc.symbol->ValueIsAddress()) {
                if (sc.symbol->GetAddressRef().GetSection() != GetSection()) {
                  // don't show the module if the symbol is a trampoline symbol
                  show_stop_context = false;
                }
              }
            }
            if (show_stop_context) {
              // We have a function or a symbol from the same
              // sections as this address.
              sc.DumpStopContext(s, exe_scope, *this, show_fullpaths,
                                 show_module, show_inlined_frames,
                                 show_function_arguments, show_function_name);
            } else {
              // We found a symbol but it was in a different
              // section so it isn't the symbol we should be
              // showing, just show the section name + offset
              Dump(s, exe_scope, DumpStyleSectionNameOffset);
            }
          }
        }
      }
    } else {
      if (fallback_style != DumpStyleInvalid)
        return Dump(s, exe_scope, fallback_style, DumpStyleInvalid, addr_size);
      return false;
    }
    break;

  case DumpStyleDetailedSymbolContext:
    if (IsSectionOffset()) {
      ModuleSP module_sp(GetModule());
      if (module_sp) {
        SymbolContext sc;
        module_sp->ResolveSymbolContextForAddress(
            *this, eSymbolContextEverything | eSymbolContextVariable, sc);
        if (sc.symbol) {
          // If we have just a symbol make sure it is in the same section
          // as our address. If it isn't, then we might have just found
          // the last symbol that came before the address that we are
          // looking up that has nothing to do with our address lookup.
          if (sc.symbol->ValueIsAddress() &&
              sc.symbol->GetAddressRef().GetSection() != GetSection())
            sc.symbol = nullptr;
        }
        sc.GetDescription(s, eDescriptionLevelBrief, target);

        if (sc.block) {
          bool can_create = true;
          bool get_parent_variables = true;
          bool stop_if_block_is_inlined_function = false;
          VariableList variable_list;
          sc.block->AppendVariables(can_create, get_parent_variables,
                                    stop_if_block_is_inlined_function,
                                    [](Variable *) { return true; },
                                    &variable_list);

          const size_t num_variables = variable_list.GetSize();
          for (size_t var_idx = 0; var_idx < num_variables; ++var_idx) {
            Variable *var = variable_list.GetVariableAtIndex(var_idx).get();
            if (var && var->LocationIsValidForAddress(*this)) {
              s->Indent();
              s->Printf("   Variable: id = {0x%8.8" PRIx64 "}, name = \"%s\"",
                        var->GetID(), var->GetName().GetCString());
              Type *type = var->GetType();
              if (type)
                s->Printf(", type = \"%s\"", type->GetName().GetCString());
              else
                s->PutCString(", type = <unknown>");
              s->PutCString(", location = ");
              var->DumpLocationForAddress(s, *this);
              s->PutCString(", decl = ");
              var->GetDeclaration().DumpStopContext(s, false);
              s->EOL();
            }
          }
        }
      }
    } else {
      if (fallback_style != DumpStyleInvalid)
        return Dump(s, exe_scope, fallback_style, DumpStyleInvalid, addr_size);
      return false;
    }
    break;

  case DumpStyleResolvedPointerDescription: {
    Process *process = exe_ctx.GetProcessPtr();
    if (process) {
      addr_t load_addr = GetLoadAddress(target);
      if (load_addr != LLDB_INVALID_ADDRESS) {
        Error memory_error;
        addr_t dereferenced_load_addr =
            process->ReadPointerFromMemory(load_addr, memory_error);
        if (dereferenced_load_addr != LLDB_INVALID_ADDRESS) {
          Address dereferenced_addr;
          if (dereferenced_addr.SetLoadAddress(dereferenced_load_addr,
                                               target)) {
            StreamString strm;
            if (dereferenced_addr.Dump(&strm, exe_scope,
                                       DumpStyleResolvedDescription,
                                       DumpStyleInvalid, addr_size)) {
              s->Address(dereferenced_load_addr, addr_size, " -> ", " ");
              s->Write(strm.GetData(), strm.GetSize());
              return true;
            }
          }
        }
      }
    }
    if (fallback_style != DumpStyleInvalid)
      return Dump(s, exe_scope, fallback_style, DumpStyleInvalid, addr_size);
    return false;
  } break;
  }

  return true;
}