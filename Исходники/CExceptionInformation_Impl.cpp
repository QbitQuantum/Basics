/**
 * Returns the name of the module in which the exception occured, or
 * an emtpy string if the module could not be found.
 *
 * @return <code>true</code> if successful, <code>false</code> otherwise.
 */
bool CExceptionInformation_Impl::GetModule ( char * szOutputBuffer, int nOutputNameLength, void** ppModuleBaseAddress )
{
   HMODULE hModule;

   if (szOutputBuffer == NULL)
      return false;

   /*
    * NUL out the first char in the output buffer.
    */
   szOutputBuffer[0] = 0;

   if ( nOutputNameLength == 0 )
      return false;

   /*
    * GetModuleHandleExA isn't supported under Windows 2000.
    */
   typedef BOOL (WINAPI * _pfnGetModuleHandleExA) ( DWORD, LPCSTR, HMODULE * );

   /*
    * Get kernel32.dll's HMODULE.
    */
   HMODULE hKern32 = GetModuleHandle("kernel32.dll");
   if ( NULL == hKern32 )  
      return false;

   /*
    * See if we're able to use GetModuleHandleExA.  According to Microsoft,
    * this API is only available on Windows XP and Vista.
    */
   _pfnGetModuleHandleExA pfnGetModuleHandleExA = 
      (_pfnGetModuleHandleExA)GetProcAddress(hKern32, "GetModuleHandleExA");

   /*
    * TODO:  Possibly use our own code to do this for other systems.
    * It is possible to enumerate all modules and get their starting/ending
    * offsets, so it would just be a simple comparison of addresses to
    * do this...
    */
   if (NULL == pfnGetModuleHandleExA)
      return false;
   
   if ( 0 == pfnGetModuleHandleExA ( 
               0x00000004 /*GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS*/, 
               (LPCSTR)m_pAddress,
               &hModule ) )
   {
      return false;
   }

   *ppModuleBaseAddress = hModule;

   if ( 0 != GetModuleFileNameA ( 
                hModule, 
                szOutputBuffer,
                nOutputNameLength ) )
   {
      /*
       * GetModuleFileNameA will return nOutputNameLength to us
       * if the buffer is too small.  NUL term the buffer.
       *
       * TODO:  Check GetLastError() and actually grow the buffer
       * and retry if it is too small.
       */ 
      if (nOutputNameLength)
         szOutputBuffer[nOutputNameLength-1] = 0;

      return true;
   }

   szOutputBuffer[0] = 0;

   return false;
}