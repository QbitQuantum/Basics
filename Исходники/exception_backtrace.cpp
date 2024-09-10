OffsetBacktrace
backtrace_to_offset_backtrace(const Backtrace & backtrace) {
  HMODULE exe_module;
  auto success = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    (LPCWSTR) &backtrace_to_offset_backtrace,
                                    &exe_module);
  if (!success) abort();

  std::vector<ptrdiff_t> stack_trace;
  for (const auto & addr : backtrace) {
    // find module of function
    HMODULE return_addr_module;
    auto success2 = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                       // NB: we subtract one because the return address might be after the
                                       //     last byte in the module (remote chance of this happening for noreturn functions)
                                       (LPCWSTR) ((char *) addr - 1),
                                       &return_addr_module);

    stack_trace.push_back(!success2
                          ? (ptrdiff_t) -1
                          : return_addr_module == exe_module
                          ? pointer_difference_in_bytes(addr, (decltype(addr)) exe_module)
                          : 0);
  }

  return stack_trace;
}