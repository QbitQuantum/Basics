ConstString ObjectFile::GetNextSyntheticSymbolName() {
  StreamString ss;
  ConstString file_name = GetModule()->GetFileSpec().GetFilename();
  ss.Printf("___lldb_unnamed_symbol%u$$%s", ++m_synthetic_symbol_idx,
            file_name.GetCString());
  return ConstString(ss.GetData());
}