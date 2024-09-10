 virtual int executeCommand(LSA_HANDLE lsa, PSID sid) {
   LPTSTR sSid;
   if (0 == ConvertSidToStringSid(sid, &sSid)) {
     LOG.LogErrorFormat(L"Failed to convert SID to string. %s", LOG.GetLastError());
     return 1;
   }
   LOG.LogInfoFormat(L"User token opened: SID=%s", sSid);
   LocalFree(sSid);
   return 0;
 }