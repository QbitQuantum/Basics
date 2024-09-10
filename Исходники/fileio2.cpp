//===============================================================================================
// FUNCTION: _AllocReadWriteBuffer
// PURPOSE:  Allocate read/write buffers for this file
//
static BOOL AllocReadWriteBuffer(ATF_FILEINFO *pATF, DWORD dwDesiredAccess)
{
   WPTRASSERT(pATF);

   // init all settings:
   pATF->lBufSize       = 0L;
   pATF->lPos           = 0L;
   pATF->lBufReadLimit  = 0L;
   pATF->pszBuf         = NULL;
   pATF->bRead          = TRUE;

   // if querying only:
   if (dwDesiredAccess == 0)
      return TRUE;

#if defined(_MSC_VER)
   char szRootDir[_MAX_DRIVE+2];
   if (_GetRootDir(pATF->pszFileName, szRootDir, sizeof(szRootDir)))
   {
      DWORD dwSectorsPerCluster     = 0;
      DWORD dwBytesPerSector        = 0;
      DWORD dwNumberOfFreeClusters  = 0;
      DWORD dwTotalNumberOfClusters = 0;
      GetDiskFreeSpaceA(szRootDir, &dwSectorsPerCluster, &dwBytesPerSector, 
                       &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
      pATF->lBufSize = min((dwSectorsPerCluster * dwBytesPerSector), (long)ATF_MAX_BUFFER_SIZE);
      ASSERT(pATF->lBufSize > 0);
   }
   else
      pATF->lBufSize = ATF_MAX_BUFFER_SIZE;
#else
      pATF->lBufSize = ATF_MAX_BUFFER_SIZE;
#endif
      
   // Allocate one more than the size for zero termination.
   pATF->pszBuf = (char *)calloc(pATF->lBufSize+1, sizeof(char));
   if (pATF->pszBuf == NULL)
   {
      pATF->lBufSize   = 0L;
      return FALSE;
   }

   pATF->lPos          = pATF->lBufSize;    // empty read buffer
   pATF->lBufReadLimit = pATF->lBufSize;
   return TRUE;
}