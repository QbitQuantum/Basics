//-----------------------------------------------------------------------------
// CZLib::AddFile
//
// Adds a file to the zip archive
//
BOOL CZLib::AddFile(string f_file)
{
   BOOL bReturn = FALSE;

   // Open file being added
   HANDLE hFile = NULL;
   hFile = CreateFile(f_file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if (hFile)
   {
      // Get file creation date
      FILETIME       ft = CUtility::getLastWriteFileTime(f_file);
      zip_fileinfo   zi = {0};

      FileTimeToDosDateTime(
         &ft,                       // last write FILETIME
         ((LPWORD)&zi.dosDate)+1,   // dos date
         ((LPWORD)&zi.dosDate)+0);  // dos time

      // Trim path off file name
      string sFileName = f_file.substr(f_file.find_last_of(_T('\\')) + 1);

      // Start a new file in Zip
      if (ZIP_OK == zipOpenNewFileInZip(m_zf, 
                                        sFileName.c_str(), 
                                        &zi, 
                                        NULL, 
                                        0, 
                                        NULL, 
                                        0, 
                                        NULL, 
                                        Z_DEFLATED, 
                                        Z_BEST_COMPRESSION))
      {
         // Write file to Zip in 4 KB chunks 
         const DWORD BUFFSIZE    = 4096;
         TCHAR buffer[BUFFSIZE]  = _T("");
         DWORD dwBytesRead       = 0;

         while (ReadFile(hFile, &buffer, BUFFSIZE, &dwBytesRead, NULL)
                && dwBytesRead)
         {
            if (ZIP_OK == zipWriteInFileInZip(m_zf, buffer, dwBytesRead)
               && dwBytesRead < BUFFSIZE)
            {
               // Success
               bReturn = TRUE;
            }
         }

         bReturn &= (ZIP_OK == zipCloseFileInZip(m_zf));
      }
      
      bReturn &= CloseHandle(hFile);
   }

   return bReturn;
}