bool OptionValue::DumpQualifiedName(Stream &strm) const {
  bool dumped_something = false;
  lldb::OptionValueSP m_parent_sp(m_parent_wp.lock());
  if (m_parent_sp) {
    if (m_parent_sp->DumpQualifiedName(strm))
      dumped_something = true;
  }
  ConstString name(GetName());
  if (name) {
    if (dumped_something)
      strm.PutChar('.');
    else
      dumped_something = true;
    strm << name;
  }
  return dumped_something;
}