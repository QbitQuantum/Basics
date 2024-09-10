bool lldb_private::formatters::swift::SwiftOptionSetSummaryProvider::
    FormatObject(ValueObject *valobj, std::string &dest,
                 const TypeSummaryOptions &options) {
  auto rawValue_sp = GetRawValue(valobj);
  if (!rawValue_sp)
    return false;

  llvm::APInt value;
  if (ReadValueIfAny(*rawValue_sp, value)) {
    FillCasesIfNeeded();

    StreamString ss;
    bool first_match = true;
    bool any_match = false;

    llvm::APInt matched_value(llvm::APInt::getNullValue(64));

    auto iter = m_cases->begin(), end = m_cases->end();
    for (; iter != end; ++iter) {
      llvm::APInt case_value = iter->first;
      if ((case_value & value) == case_value) {
        // hey a case matched!!
        any_match = true;
        if (first_match) {
          ss.Printf("[.%s", iter->second.AsCString());
          first_match = false;
        } else {
          ss.Printf(", .%s", iter->second.AsCString());
        }

        matched_value |= case_value;

        // if we matched everything, get out
        if (matched_value == value)
          break;
      }
    }

    if (any_match) {
      // if we found a full match, then close the list
      if (matched_value == value)
        ss.PutChar(']');
      else {
        // print the unaccounted-for bits separately
        llvm::APInt residual = (value & ~matched_value);
        ss.Printf(", 0x%s]", residual.toString(16, false).c_str());
      }
    }

    // if we printed anything, use it
    const char *data = ss.GetData();
    if (data && data[0]) {
      dest.assign(data);
      return true;
    }
  }
  return false;
}