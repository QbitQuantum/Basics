int TraverseDirectoryTreeW (
   LPCWSTR pszPath, 
   LPCWSTR pszPattern, 
   DWORD   fdwFlags, 
   PFNTraverseDirectoryTreeCallbackW pfnCallback, 
   LPVOID  pvUser,
   int     nCurrentDepth)
{
   bool fSubdirs    = (fdwFlags & TDT_SUBDIRS) != 0;
   bool fDiagnostic = (fdwFlags & TDT_DIAGNOSTIC) != 0;
   //bool fDirFirst   = (fdwFlags & TDT_DIRFIRST) != 0;
   //bool fDirLast    = (fdwFlags & TDT_DIRLAST) != 0;

   if (fDiagnostic)
      {
      if (pszPattern)
         bprintfl(*g_pbpDiag, "TDT[%d]: %04x path = '%s' pattern = '%s' subdirs = %d", nCurrentDepth, fdwFlags, pszPath, pszPattern, fSubdirs);
      else
         bprintfl(*g_pbpDiag, "TDT[%d]: %04x path = '%s' pattern = NULL subdirs = %d", nCurrentDepth, fdwFlags, pszPath, fSubdirs);
      }

   // build a string containing path\pattern, we will pass this
   // into FindFirstFile. there are some special cases.
   // we treat paths that end in \ as meaning path\*.
   // we replace *.* with * since it means the same thing and
   // is easier to parse. (this is a special case go back to DOS). 
   //
   int cchPath = lstrlenW(pszPath);
   int cchMax = cchPath + MAX_PATH + 2;
   LPWSTR psz = (LPWSTR)malloc(cchMax * sizeof(WCHAR));
   lstrcpyW(psz, pszPath);
   LPWSTR pszNext = psz + lstrlenW(psz);

   bool fMatchAll = false;
   if (pszPattern && pszPattern[0])
      {
      if (0 == lstrcmpW(pszPattern, L"*.*") || 0 == lstrcmpW(pszPattern, L"*"))
         {
         fMatchAll = true;
         }
      pszNext = PathAddBackslashW(psz);
      lstrcpyW(pszNext, pszPattern);
      }
   else if (pszNext > psz && (pszNext[-1] == '\\' || pszNext[-1] == '/'))
      {
      fMatchAll = true;
      pszNext[0] = '*';
      pszNext[1] = 0;
      }

   HRESULT hr = S_OK;
   int err = ERROR_SUCCESS;
   int ixCurrentItem = 0;
   DWORD dwFirst = TDT_FIRST;

   LinkedFindData * pdirs = NULL;

   WIN32_FIND_DATAW wfd;
   HANDLE hFind = FindFirstFileW(psz, &wfd);
   if (INVALID_HANDLE_VALUE == hFind) 
      {
      err = GetLastError();
      // if we can't open the directory because of an access denied error
      // it might be the DACLs that are causing the problem. If so, then
      // just remove the dacls. we are going to be deleting the directory
      // anway...
      //
      if (ERROR_ACCESS_DENIED == err)
         {
         int errT = RemoveFileDACLs(pszPath, fdwFlags & TDT_DIAGNOSTIC, g_pbpDiag);
         if (errT)
            err = errT;
         else
            {
            hFind = FindFirstFileW(psz, &wfd);
            if (INVALID_HANDLE_VALUE == hFind) 
               {
               errT = GetLastError();
               if (errT != err)
                  ReportErrorW(errT, "FindFirstFile ", psz);
               }
            else
               {
               err = 0;
               }
            }
         }
      if (err)
         ReportErrorW(err, "FindFirstFile ", psz);
      }

   if (hFind && INVALID_HANDLE_VALUE != hFind)
      {
      do {
         // ignore . and ..
         if (IsDotOrDotDot(wfd.cFileName))
            continue;

         ++ixCurrentItem;

         bool fSkip = false;
         if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
            // if we are recursing, and we happen to be matching all, then remember this
            // directory for later (so we don't need to enumerate again for dirs).
            // otherwise we will have to re-enumerate in this directory to get subdirs.
            if (fSubdirs && fMatchAll) 
               {
               LinkedFindData * pdir = (LinkedFindData*)malloc(sizeof(LinkedFindData));
               pdir->wfd = wfd;
               pdir->next = pdirs;
               pdirs = pdir;
               fSkip = true;  // we will do the callback for this directory later, if at all.
               }
            else if (fdwFlags & TDT_NODIRS)
               fSkip = true;
            }
         else
            {
            if (fdwFlags & TDT_NOFILES)
               fSkip = true;
            }

         if (fDiagnostic)
            bprintfl (*g_pbpDiag, "TDT[%d]: 0x%08x %s %s", nCurrentDepth, wfd.dwFileAttributes, wfd.cFileName, fSkip ? "<skip>" : "");

         if ( ! fSkip)
            {
            lstrcpyW(pszNext, wfd.cFileName); 
            if ( ! pfnCallback(pvUser, psz, pszNext - psz, (fdwFlags & ~(TDT_DIRLAST | TDT_DIRFIRST)) | dwFirst, nCurrentDepth, ixCurrentItem, wfd))
               break;
            dwFirst = 0;
            }

         } while (FindNextFileW(hFind, &wfd));

         if (fDiagnostic)
            bprintfl (*g_pbpDiag, "TDT[%d]: Done with %s %s", nCurrentDepth, pszPath, pszPattern);
      }

   // we want to traverse subdirs, but we were unable to build a list of dirs when we 
   // enumerated the files, so re-enumerate with * to get the directories.
   if (fSubdirs && ! fMatchAll)
      {
      if (hFind && INVALID_HANDLE_VALUE != hFind)
         FindClose(hFind);

      lstrcpyW(pszNext, L"*");
      hFind = FindFirstFileW(psz, &wfd);
      if (INVALID_HANDLE_VALUE != hFind) 
         {
         do {
            if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && ! IsDotOrDotDot(wfd.cFileName))
               {
               LinkedFindData * pdir = (LinkedFindData*)malloc(sizeof(LinkedFindData));
               pdir->wfd = wfd;
               pdir->next = pdirs;
               pdirs = pdir;
               }

            } while (FindNextFileW(hFind, &wfd));
         }
      }

   err = GetLastError();
   if (ERROR_NO_MORE_FILES == err)
      err = ERROR_SUCCESS;

   // now traverse and callback subdirectories.
   //
   if (fSubdirs && pdirs)
      {
      pdirs = ReverseLinkedList(pdirs);
      while (pdirs)
         {
         LinkedFindData * pdir = pdirs;
         pdirs = pdirs->next;

         lstrcpyW(pszNext, pdir->wfd.cFileName); 
         if ((fdwFlags & TDT_DIRFIRST) && ! (fdwFlags & TDT_NODIRS))
            {
            if (fDiagnostic)
               bprintfl (*g_pbpDiag, "TDT[%d]: DIRFIRST 0x%08x %s %s", nCurrentDepth, pszPath, pszPattern);

            if ( ! pfnCallback(pvUser, psz, pszNext - psz, TDT_DIRFIRST | (fdwFlags & ~TDT_DIRLAST) | dwFirst, nCurrentDepth, ixCurrentItem, pdir->wfd))
               break;
            dwFirst = 0;
            }

         err = TraverseDirectoryTreeW(psz, pszPattern, fdwFlags, pfnCallback, pvUser, nCurrentDepth+1);

         if ((fdwFlags & TDT_DIRLAST) && ! (fdwFlags & TDT_NODIRS))
            {
            if (fDiagnostic)
               bprintfl (*g_pbpDiag, "TDT[%d]: DIRLAST 0x%08x %s %s", nCurrentDepth, pszPath, pszPattern);

            if ( ! pfnCallback(pvUser, psz, pszNext - psz, TDT_DIRLAST | (fdwFlags & ~TDT_DIRFIRST) | dwFirst, nCurrentDepth, ixCurrentItem, pdir->wfd))
               break;
            dwFirst = 0;
            }
         }
      }


   if (hFind && INVALID_HANDLE_VALUE != hFind)
      FindClose(hFind);

   return err;
}