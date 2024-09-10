void COptex::CommonConstructor(DWORD dwSpinCount, 
   BOOL fUnicode, PVOID pszName) {

   if (sm_fUniprocessorHost == -1) {
      // This is the 1st object constructed, get the number of CPUs
      SYSTEM_INFO sinf;
      GetSystemInfo(&sinf);
      sm_fUniprocessorHost = (sinf.dwNumberOfProcessors == 1);
   }


   m_hevt = m_hfm = NULL;
   m_psi  = NULL;

   if (pszName == NULL) {  // Creating a single-process optex

      m_hevt = CreateEventA(NULL, FALSE, FALSE, NULL);
      chASSERT(m_hevt != NULL);

      m_psi = new SHAREDINFO;
      chASSERT(m_psi != NULL);
      ZeroMemory(m_psi, sizeof(*m_psi));

   } else {                // Creating a cross-process optex

      // Always use ANSI so that this works on Win9x and Windows 2000
      char szResult[100];
      ConstructObjectName(szResult, "Optex_Event_", fUnicode, pszName);
      m_hevt = CreateEventA(NULL, FALSE, FALSE, szResult);
      chASSERT(m_hevt != NULL);

      ConstructObjectName(szResult, "Optex_MMF_", fUnicode, pszName);
      m_hfm = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, 
         PAGE_READWRITE, 0, sizeof(*m_psi), szResult);
      chASSERT(m_hfm != NULL);

      m_psi = (PSHAREDINFO) MapViewOfFile(m_hfm, 
         FILE_MAP_WRITE, 0, 0, 0);
      chASSERT(m_psi != NULL);

      // Note: SHAREDINFO's m_lLockCount, m_dwThreadId, and m_lRecurseCount
      // members need to be initialized to 0. Fortunately, a new pagefile 
      // MMF sets all of its data to 0 when created. This saves use from 
      // some thread synchronization work.
   }

   SetSpinCount(dwSpinCount);
}