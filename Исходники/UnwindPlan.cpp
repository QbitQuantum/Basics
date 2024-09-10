void UnwindPlan::Row::RegisterLocation::Dump(Stream &s,
                                             const UnwindPlan *unwind_plan,
                                             const UnwindPlan::Row *row,
                                             Thread *thread,
                                             bool verbose) const {
  switch (m_type) {
  case unspecified:
    if (verbose)
      s.PutCString("=<unspec>");
    else
      s.PutCString("=!");
    break;
  case undefined:
    if (verbose)
      s.PutCString("=<undef>");
    else
      s.PutCString("=?");
    break;
  case same:
    s.PutCString("= <same>");
    break;

  case atCFAPlusOffset:
  case isCFAPlusOffset: {
    s.PutChar('=');
    if (m_type == atCFAPlusOffset)
      s.PutChar('[');
    s.Printf("CFA%+d", m_location.offset);
    if (m_type == atCFAPlusOffset)
      s.PutChar(']');
  } break;

  case atAFAPlusOffset:
  case isAFAPlusOffset: {
    s.PutChar('=');
    if (m_type == atAFAPlusOffset)
      s.PutChar('[');
    s.Printf("AFA%+d", m_location.offset);
    if (m_type == atAFAPlusOffset)
      s.PutChar(']');
  } break;

  case inOtherRegister: {
    const RegisterInfo *other_reg_info = nullptr;
    if (unwind_plan)
      other_reg_info = unwind_plan->GetRegisterInfo(thread, m_location.reg_num);
    if (other_reg_info)
      s.Printf("=%s", other_reg_info->name);
    else
      s.Printf("=reg(%u)", m_location.reg_num);
  } break;

  case atDWARFExpression:
  case isDWARFExpression: {
    s.PutChar('=');
    if (m_type == atDWARFExpression)
      s.PutChar('[');
    DumpDWARFExpr(
        s, llvm::makeArrayRef(m_location.expr.opcodes, m_location.expr.length),
        thread);
    if (m_type == atDWARFExpression)
      s.PutChar(']');
  } break;
  }
}