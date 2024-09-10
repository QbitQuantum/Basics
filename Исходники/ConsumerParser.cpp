void ConsumerParserClass::Print(const wchar_t* outlog, const wchar_t* szNamespace, const wchar_t* szType) {
  FILE* out = CreateLogFile(outlog, L"at, ccs=UNICODE");
  std::vector<DWORD> *allocMap = Map.GetDataAllocMap();
  if (allocMap) {
    if (szType)
      MyPrintFunc(out, L"==== %s in namespace %s ====\n", szType, szNamespace);
    else
      MyPrintFunc(out, L"==== Consumers in namespace %s ====\n", szNamespace);
    std::vector<InstanceStruct>::iterator it = Consumers.begin();
    for (; it != Consumers.end(); ++it) {
      MyPrintFunc(out, L"[%S]:\nConsumer:(%.8X.%.8X.%.8X)\n", it->InstanceID, it->Location.LogicalID, it->Location.RecordID, it->Location.Size);
      EventConsumer* p = EventConsumer::Create(m_ObjFile, *allocMap, *it, szType, m_bXP);
      if (p) {
        p->Print(m_ObjFile, out);
        delete p;
      }
    }
    MyPrintFunc(out, L"=============================================================================\n");
    if (out)
      ::fclose(out);
  }
}