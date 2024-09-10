std::string CXXSyntheticChildren::GetDescription() {
  StreamString sstr;
  sstr.Printf("%s%s%s %s", Cascades() ? "" : " (not cascading)",
              SkipsPointers() ? " (skip pointers)" : "",
              SkipsReferences() ? " (skip references)" : "",
              m_description.c_str());

  return sstr.GetString();
}