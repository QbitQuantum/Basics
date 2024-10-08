bool
ItaniumABILanguageRuntime::GetDynamicTypeAndAddress (ValueObject &in_value, 
                                                     lldb::DynamicValueType use_dynamic, 
                                                     TypeAndOrName &class_type_or_name, 
                                                     Address &dynamic_address)
{
    // For Itanium, if the type has a vtable pointer in the object, it will be at offset 0
    // in the object.  That will point to the "address point" within the vtable (not the beginning of the
    // vtable.)  We can then look up the symbol containing this "address point" and that symbol's name 
    // demangled will contain the full class name.
    // The second pointer above the "address point" is the "offset_to_top".  We'll use that to get the
    // start of the value object which holds the dynamic type.
    //
    
    class_type_or_name.Clear();
    
    // Only a pointer or reference type can have a different dynamic and static type:
    if (CouldHaveDynamicValue (in_value))
    {
        // First job, pull out the address at 0 offset from the object.
        AddressType address_type;
        lldb::addr_t original_ptr = in_value.GetPointerValue(&address_type);
        if (original_ptr == LLDB_INVALID_ADDRESS)
            return false;
        
        ExecutionContext exe_ctx (in_value.GetExecutionContextRef());

        Target *target = exe_ctx.GetTargetPtr();
        Process *process = exe_ctx.GetProcessPtr();

        char memory_buffer[16];
        DataExtractor data(memory_buffer, sizeof(memory_buffer), 
                           process->GetByteOrder(), 
                           process->GetAddressByteSize());
        size_t address_byte_size = process->GetAddressByteSize();
        Error error;
        size_t bytes_read = process->ReadMemory (original_ptr, 
                                                 memory_buffer, 
                                                 address_byte_size, 
                                                 error);
        if (!error.Success() || (bytes_read != address_byte_size))
        {
            return false;
        }
        
        lldb::offset_t offset = 0;
        lldb::addr_t vtable_address_point = data.GetAddress (&offset);
            
        if (offset == 0)
            return false;
        
        // Now find the symbol that contains this address:
        
        SymbolContext sc;
        Address address_point_address;
        if (target && !target->GetSectionLoadList().IsEmpty())
        {
            if (target->GetSectionLoadList().ResolveLoadAddress (vtable_address_point, address_point_address))
            {
                target->GetImages().ResolveSymbolContextForAddress (address_point_address, eSymbolContextSymbol, sc);
                Symbol *symbol = sc.symbol;
                if (symbol != NULL)
                {
                    const char *name = symbol->GetMangled().GetDemangledName().AsCString();
                    if (strstr(name, vtable_demangled_prefix) == name)
                    {
                        Log *log (lldb_private::GetLogIfAllCategoriesSet (LIBLLDB_LOG_OBJECT));
                        if (log)
                            log->Printf ("0x%16.16" PRIx64 ": static-type = '%s' has vtable symbol '%s'\n",
                                         original_ptr,
                                         in_value.GetTypeName().GetCString(),
                                         name);
                        // We are a C++ class, that's good.  Get the class name and look it up:
                        const char *class_name = name + strlen(vtable_demangled_prefix);
                        class_type_or_name.SetName (class_name);
                        const bool exact_match = true;
                        TypeList class_types;
                        
                        uint32_t num_matches = 0;
                        // First look in the module that the vtable symbol came from
                        // and look for a single exact match.
                        if (sc.module_sp)
                        {
                            num_matches = sc.module_sp->FindTypes (sc,
                                                                   ConstString(class_name),
                                                                   exact_match,
                                                                   1,
                                                                   class_types);
                        }
                        
                        // If we didn't find a symbol, then move on to the entire
                        // module list in the target and get as many unique matches
                        // as possible
                        if (num_matches == 0)
                        {
                            num_matches = target->GetImages().FindTypes (sc,
                                                                         ConstString(class_name),
                                                                         exact_match,
                                                                         UINT32_MAX,
                                                                         class_types);
                        }
                        
                        lldb::TypeSP type_sp;
                        if (num_matches == 0)
                        {
                            if (log)
                                log->Printf("0x%16.16" PRIx64 ": is not dynamic\n", original_ptr);
                            return false;
                        }
                        if (num_matches == 1)
                        {
                            type_sp = class_types.GetTypeAtIndex(0);
                            if (log)
                                log->Printf ("0x%16.16" PRIx64 ": static-type = '%s' has dynamic type: uid={0x%" PRIx64 "}, type-name='%s'\n",
                                             original_ptr,
                                             in_value.GetTypeName().AsCString(),
                                             type_sp->GetID(),
                                             type_sp->GetName().GetCString());

                            class_type_or_name.SetTypeSP(class_types.GetTypeAtIndex(0));
                        }
                        else if (num_matches > 1)
                        {
                            size_t i;
                            if (log)
                            {
                                for (i = 0; i < num_matches; i++)
                                {
                                    type_sp = class_types.GetTypeAtIndex(i);
                                    if (type_sp)
                                    {
                                        if (log)
                                            log->Printf ("0x%16.16" PRIx64 ": static-type = '%s' has multiple matching dynamic types: uid={0x%" PRIx64 "}, type-name='%s'\n",
                                                         original_ptr,
                                                         in_value.GetTypeName().AsCString(),
                                                         type_sp->GetID(),
                                                         type_sp->GetName().GetCString());
                                    }
                                }
                            }

                            for (i = 0; i < num_matches; i++)
                            {
                                type_sp = class_types.GetTypeAtIndex(i);
                                if (type_sp)
                                {
                                    if (type_sp->GetClangFullType().IsCXXClassType())
                                    {
                                        if (log)
                                            log->Printf ("0x%16.16" PRIx64 ": static-type = '%s' has multiple matching dynamic types, picking this one: uid={0x%" PRIx64 "}, type-name='%s'\n",
                                                         original_ptr,
                                                         in_value.GetTypeName().AsCString(),
                                                         type_sp->GetID(),
                                                         type_sp->GetName().GetCString());
                                        class_type_or_name.SetTypeSP(type_sp);
                                        break;
                                    }
                                }
                            }
                            
                            if (i == num_matches)
                            {
                                if (log)
                                    log->Printf ("0x%16.16" PRIx64 ": static-type = '%s' has multiple matching dynamic types, didn't find a C++ match\n",
                                                 original_ptr,
                                                 in_value.GetTypeName().AsCString());
                                return false;
                            }
                        }

                        // There can only be one type with a given name,
                        // so we've just found duplicate definitions, and this
                        // one will do as well as any other.
                        // We don't consider something to have a dynamic type if
                        // it is the same as the static type.  So compare against
                        // the value we were handed.
                        if (type_sp)
                        {
                            if (ClangASTContext::AreTypesSame (in_value.GetClangType(),
                                                               type_sp->GetClangFullType()))
                            {
                                // The dynamic type we found was the same type,
                                // so we don't have a dynamic type here...
                                return false;
                            }

                            // The offset_to_top is two pointers above the address.
                            Address offset_to_top_address = address_point_address;
                            int64_t slide = -2 * ((int64_t) target->GetArchitecture().GetAddressByteSize());
                            offset_to_top_address.Slide (slide);
                            
                            Error error;
                            lldb::addr_t offset_to_top_location = offset_to_top_address.GetLoadAddress(target);
                            
                            size_t bytes_read = process->ReadMemory (offset_to_top_location, 
                                                                     memory_buffer, 
                                                                     address_byte_size, 
                                                                     error);
                                                                     
                            if (!error.Success() || (bytes_read != address_byte_size))
                            {
                                return false;
                            }
                            
                            offset = 0;
                            int64_t offset_to_top = data.GetMaxS64(&offset, process->GetAddressByteSize());
                            
                            // So the dynamic type is a value that starts at offset_to_top
                            // above the original address.
                            lldb::addr_t dynamic_addr = original_ptr + offset_to_top;
                            if (!target->GetSectionLoadList().ResolveLoadAddress (dynamic_addr, dynamic_address))
                            {
                                dynamic_address.SetRawAddress(dynamic_addr);
                            }
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return class_type_or_name.IsEmpty() == false;
}