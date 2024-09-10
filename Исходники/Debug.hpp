            std::string format_address_win32(const void* addr) const
            {
                if (!dbghelp.initialized())
                    return format_address_fallback(addr);

                DWORD64 symbol_info_buf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
                const auto symbol_info = reinterpret_cast<SYMBOL_INFO*>(symbol_info_buf);
                symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
                symbol_info->MaxNameLen = MAX_SYM_NAME;

                IMAGEHLP_MODULE64 module_info;
                module_info.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

                DWORD64 symbol_offset;

                const auto symbol_resolved = SymFromAddr(
                    GetCurrentProcess(),
                    reinterpret_cast<DWORD64>(addr),
                    &symbol_offset,
                    symbol_info);

                if (symbol_resolved)
                {
                    const auto module_resolved = SymGetModuleInfo64(
                        GetCurrentProcess(),
                        symbol_info->ModBase,
                        &module_info);

                    if (module_resolved)
                    {
                        return format_symbol(
                            module_info.ModuleName,
                            symbol_info->Name,
                            reinterpret_cast<const void*>(symbol_offset));
                    }
                    else
                    {
                        return format_symbol(symbol_info->Name, addr);
                    }
                }
                else
                {
                    const auto module_resolved = SymGetModuleInfo64(
                        GetCurrentProcess(),
                        reinterpret_cast<DWORD64>(addr),
                        &module_info);

                    if (module_resolved)
                    {
                        const auto module_offset = reinterpret_cast<const char*>(addr) - module_info.BaseOfImage;
                        return format_module(module_info.ModuleName, module_offset);
                    }
                    else
                    {
                        return format_address_fallback(addr);
                    }
                }
            }