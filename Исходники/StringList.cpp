void StringList::LogDump(Log *log, const char *name) {
  if (!log)
    return;

  StreamString strm;
  if (name)
    strm.Printf("Begin %s:\n", name);
  for (const auto &s : m_strings) {
    strm.Indent();
    strm.Printf("%s\n", s.c_str());
  }
  if (name)
    strm.Printf("End %s.\n", name);

  LLDB_LOGV(log, "{0}", strm.GetData());
}