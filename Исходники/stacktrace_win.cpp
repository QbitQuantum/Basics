 /**
  * Get the display name of the executable module containing the specified address.
  * 
  * @param process               Process handle
  * @param address               Address to find
  * @param returnedModuleName    Returned module name
  */
 static void getModuleName( HANDLE process, DWORD64 address, std::string* returnedModuleName ) {
     IMAGEHLP_MODULE64 module64;
     memset ( &module64, 0, sizeof(module64) );
     module64.SizeOfStruct = sizeof(module64);
     BOOL ret = SymGetModuleInfo64( process, address, &module64 );
     if ( FALSE == ret ) {
         returnedModuleName->clear();
         return;
     }
     char* moduleName = module64.LoadedImageName;
     char* backslash = strrchr( moduleName, '\\' );
     if ( backslash ) {
         moduleName = backslash + 1;
     }
     *returnedModuleName = moduleName;
 }