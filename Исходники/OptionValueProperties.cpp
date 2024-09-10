Error OptionValueProperties::DumpPropertyValue(const ExecutionContext *exe_ctx,
                                               Stream &strm,
                                               llvm::StringRef property_path,
                                               uint32_t dump_mask) {
  Error error;
  const bool will_modify = false;
  lldb::OptionValueSP value_sp(
      GetSubValue(exe_ctx, property_path, will_modify, error));
  if (value_sp) {
    if (!value_sp->ValueIsTransparent()) {
      if (dump_mask & eDumpOptionName)
        strm.PutCString(property_path);
      if (dump_mask & ~eDumpOptionName)
        strm.PutChar(' ');
    }
    value_sp->DumpValue(exe_ctx, strm, dump_mask);
  }
  return error;
}