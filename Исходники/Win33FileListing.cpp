int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   LPWIN32_FIND_DATAW ffd;
   LARGE_INTEGER filesize;
   WCHAR szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
   LPWSTR *szArgList;
   int argCount;

   std::ofstream logFile;
   logFile.open ("FileListing.log");

   
   // If the directory is not specified as a command-line argument,
   // print usage.

  szArgList = CommandLineToArgvW((LPCWSTR)GetCommandLine(), &argCount);

  if(argCount !=2)
	  logFile << "\nUsage: %s <directory name>\n" << szArgList[0];

   /*if(argc != 2)
   {
      _tprintf(TEXT("\nUsage: %s <directory name>\n"), argv[0]);
      return (-1);
   }*/

   // Check that the input path plus 3 is not longer than MAX_PATH.
   // Three characters are for the "\*" plus NULL appended below.

   StringCchLengthW(szArgList[1], MAX_PATH,  (size_t *)&argCount);

   if ( argCount > (MAX_PATH - 3))
   {
      logFile << "\nDirectory path is too long.\n";
      return (-1);
   }

  logFile <<"\nTarget directory is "<<szArgList[1] <<":\n\n";

   // Prepare string for use with FindFile functions. First, copy the
   // string to a buffer, then append '\*' to the directory name.

   StringCchCopyW(szDir, MAX_PATH, szArgList[1]);
   StringCchCatW(szDir, MAX_PATH, L"\\*");

   // Find the first file in the directory.

   hFind = FindFirstFileW(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) 
   {
      DisplayErrorBox(TEXT("FindFirstFile"));
      return dwError;
   } 
   
   // List all the files in the directory with some info about them.

   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
      }
      else
      {
         filesize.LowPart = ffd.nFileSizeLow;
         filesize.HighPart = ffd.nFileSizeHigh;
         _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
      DisplayErrorBox(TEXT("FindFirstFile"));
   }

   FindClose(hFind);
   return dwError;

	return 0;
}