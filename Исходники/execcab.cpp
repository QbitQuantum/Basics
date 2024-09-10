std::string cab_extract(std::string cabfilepath)
{
  string tmpdir = FileUtils::createTempFileName("JSMOOTHDIR");
  CreateDirectoryA(tmpdir.c_str(), 0);
  printf("Created %s\n", tmpdir.c_str());


  if (!SetupIterateCabinet(cabfilepath.c_str(), 0, (PSP_FILE_CALLBACK)CabinetCallback, (void *)tmpdir.c_str()))
    {
//       DEBUG("Error extract cabinet)
//       FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
// 		     FORMAT_MESSAGE_FROM_SYSTEM |
// 		     FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
// 		     GetLastError(), MAKELANGID(LANG_NEUTRAL,
// 						SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL );

//       MessageBox( NULL,(LPTSTR) lpMsgBuf,
// 		  "SetupIterateCabinet() Error :",
// 		  MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

      printf("Error extracting the cab %s\n", cabfilepath.c_str());
    }
  return tmpdir;
}