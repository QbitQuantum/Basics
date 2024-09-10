bool LibStdcppTupleSyntheticFrontEnd::Update() {
  m_members.clear();

  ValueObjectSP valobj_backend_sp = m_backend.GetSP();
  if (!valobj_backend_sp)
    return false;

  ValueObjectSP next_child_sp = valobj_backend_sp->GetNonSyntheticValue();
  while (next_child_sp != nullptr) {
    ValueObjectSP current_child = next_child_sp;
    next_child_sp = nullptr;

    size_t child_count = current_child->GetNumChildren();
    for (size_t i = 0; i < child_count; ++i) {
      ValueObjectSP child_sp = current_child->GetChildAtIndex(i, true);
      llvm::StringRef name_str = child_sp->GetName().GetStringRef();
      if (name_str.startswith("std::_Tuple_impl<")) {
        next_child_sp = child_sp;
      } else if (name_str.startswith("std::_Head_base<")) {
        ValueObjectSP value_sp =
            child_sp->GetChildMemberWithName(ConstString("_M_head_impl"), true);
        if (value_sp) {
          StreamString name;
          name.Printf("[%zd]", m_members.size());
          value_sp->SetName(ConstString(name.GetData()));

          m_members.push_back(value_sp);
        }
      }
    }
  }

  return false;
}