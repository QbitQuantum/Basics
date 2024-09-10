const JOBOBJECT_EXTENDED_LIMIT_INFORMATION& CJobObject::GetExtendedLimit() const {
   BOOL bRet;

   bRet = QueryInformationJobObject(GetHandle(), JobObjectExtendedLimitInformation,
      (PVOID) &m_Limit, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION), NULL);
   if (bRet == 0) {
      throw CCodineException(CError::GetErrorMessage(GetLastError()), __FILE__, __LINE__);
   }
   return m_Limit;
}