bool CmdExtension::processList(DebuggerProxy *proxy) {
  IDebuggable::InfoVec info;

  Array exts = Extension::GetLoadedExtensions();
  typedef std::set<std::string, string_lessi> sorted_iset;
  sorted_iset names;
  for (ArrayIter iter(exts); iter; ++iter) {
    names.insert(iter.second().toString().data());
  }
  for (sorted_iset::const_iterator iter = names.begin();
       iter != names.end(); ++iter) {
    Extension *ext = Extension::GetExtension(*iter);
    ASSERT(ext);
    if (ext) {
      int support = ext->debuggerSupport();
      string line;
      line += (support & IDebuggable::SupportInfo) ? "Yes     " : "        ";
      line += (support & IDebuggable::SupportDump) ? "Yes     " : "        ";
      line += (support & IDebuggable::SupportVerb) ? "Yes     " : "        ";
      line += ext->getVersion();
      IDebuggable::Add(info, iter->c_str(), line);
    }
  }
  int nameLen;
  String body = DebuggerClient::FormatInfoVec(info, &nameLen);
  int hrLen = nameLen + 42;
  if (hrLen > DebuggerClient::LineWidth) hrLen = DebuggerClient::LineWidth;

  StringBuffer sb;
  for (int i = 0; i < hrLen; i++) sb.append(BOX_H); sb.append("\n");
  sb.append(StringUtil::Pad("Name\\Support", nameLen));
  sb.append("Info    Dump    Verb    Version\n");
  for (int i = 0; i < hrLen; i++) sb.append(BOX_H); sb.append("\n");
  sb.append(body);
  for (int i = 0; i < hrLen; i++) sb.append(BOX_H); sb.append("\n");

  m_out = sb.detach();
  return proxy->send(this);
}