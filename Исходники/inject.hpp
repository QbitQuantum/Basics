bool MapRemoteModule(unsigned long pId, const char *module)
{
   IMAGE_DOS_HEADER *dosHd;
   IMAGE_NT_HEADERS *ntHd;
   IMAGE_NT_HEADERS64 *ntHd64 = NULL;

   HANDLE hFile = CreateFileA(module,
      GENERIC_READ,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);

   if(hFile == INVALID_HANDLE_VALUE)
      return false;

   unsigned int fSize;

   if(GetFileAttributesA(module) & FILE_ATTRIBUTE_COMPRESSED)
      fSize = GetCompressedFileSizeA(module, NULL);
   else
      fSize = GetFileSize(hFile, NULL);

   unsigned char *dllBin = new unsigned char[fSize];
   unsigned int nBytes;

   // copy into our dllBin buffer the entire DLL
   ReadFile(hFile, dllBin, fSize, (LPDWORD)&nBytes, FALSE);
   CloseHandle(hFile);

   //   Every PE file contains a little DOS stub for backwards compatibility
   //   its only real relevance is that it contains a pointer to the actual
   //   PE header.
   dosHd = MakePtr(IMAGE_DOS_HEADER *, dllBin, 0);

   //   Make sure we got a valid DOS header
   if(dosHd->e_magic != IMAGE_DOS_SIGNATURE)
   {
       wxMessageBox( _("The DOS header was invalid"), 
           _("Error:  Invalid DOS header"),
           wxICON_ERROR );
       delete [] dllBin;
       return false;
   }

   //   Get the real PE header from the DOS stub header
   //   This header contains pointers to the Optional Header and the 
   //   COFF File Header.
   ntHd = MakePtr(IMAGE_NT_HEADERS *, dllBin, dosHd->e_lfanew);

   //   Verify that the PE header is PE00
   if(ntHd->Signature != IMAGE_NT_SIGNATURE)
   {
       wxMessageBox( _("The PE Header was not found."), 
           _("Error:  PE Header not found"),
           wxICON_ERROR );
       delete [] dllBin;
       return false;
   }

   //   Verify that the image file is a DLL
   if( (ntHd->FileHeader.Characteristics & IMAGE_FILE_DLL) == false )
   {
       wxMessageBox( _("You may only inject DLL image files."), 
           _("Error:  Injected image file was not a DLL"),
           wxICON_ERROR );
       delete [] dllBin;
       return false;
   }

   // Open the target process
   HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);

   // We failed to open the process, so return false
   if(!hProcess)
   {
       wxMessageBox( _("Failed to open target process."), 
           _("Error:  Failed to open process"),
           wxICON_ERROR );
       delete [] dllBin;
       return false;
   }

   //   Determine whether the image is a PE32 or PE32+ executable
   if( ntHd->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC )
   {
        if( ntHd->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC )
        {
            ntHd64 = (IMAGE_NT_HEADERS64 *)ntHd;
            wxMessageBox( _("Image is a PE32+ executable.\nInjector Gadget doesn't support PE32+ executables yet."),
                _("Error:  Image is not a PE32 executable"),
                wxICON_ERROR );
        }
        else if( ntHd->OptionalHeader.Magic == IMAGE_ROM_OPTIONAL_HDR_MAGIC )
        {
            wxMessageBox( _("Image is a ROM image.\nInjector Gadget doesn't support ROM images."),
                _("Error:  Image is not a PE32 executable"),
                wxICON_ERROR );
        }
        delete [] dllBin;
        return false;
   }

   //   Allocate space for the module in the remote process
   void *imageBase = VirtualAllocEx(hProcess,
      NULL,
      ntHd->OptionalHeader.SizeOfImage,
      MEM_COMMIT | MEM_RESERVE,
      PAGE_EXECUTE_READWRITE);

   //   Make sure we got the memory space we wanted
   if(!imageBase)
   {
       delete [] dllBin;
       return false;
   }
   //   Allocate space for our stub
   void *stubBase = VirtualAllocEx(hProcess,
      NULL,
      MakeDelta(SIZE_T, DC_stubend, DllCall_stub),
      MEM_COMMIT | MEM_RESERVE,
      PAGE_EXECUTE_READWRITE);

   //   Make sure we got the memory space we wanted
   if(!stubBase)
   {
       delete [] dllBin;
       return false;
   }

   //   We now need to fix up the tables.
   //   The tables are as follows (in order):
   //   Export Table, Import Table, Resource Table, Exception Table,
   //   Certificate Table, Base Relocation Table, Debug, Architecture,
   //   Global Ptr, TLS Table, Load Config Table, Bound Import, IAT,
   //   Delay Import Descriptor, CLR Runtime Header, Reserved

   //   First important section is the Export Table.  We're going to skip this
   //   since the whole point of cloaking a DLL is to hide its presence.

   //   Second important section is the Import Table.  We really need this.
   if( ntHd->OptionalHeader.NumberOfRvaAndSizes > 1 )
   {
       IMAGE_IMPORT_DESCRIPTOR *impDesc = (IMAGE_IMPORT_DESCRIPTOR *)GetPtrFromRVA(
           (DWORD)(ntHd->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress),
           ntHd,
           (PBYTE)dllBin);
       if(ntHd->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)
           FixImports(pId,
           (unsigned char *)dllBin,
           ntHd,
           impDesc);
       else // size was 0 for the import directory entry
       {
           wxMessageBox(
               _("Size of import directory entry was 0"),
               _("Error:  Import Directory size is 0"),
               wxICON_ERROR);
           delete [] dllBin;
           return false;
       }
   }
   else // IMAGE_DIRECTORY_ENTRY_IMPORT didn't exist in the data directories
   {
       wxMessageBox( _("The import table referenced an invalid index in the data directory."),
           _("Error:  Import table could not be located"),
           wxICON_ERROR );
       delete [] dllBin;
       return false;
   }

   //   Fix "base relocations" of the new module.  Base relocations are places
   //   in the module that use absolute addresses to reference data.  Since
   //   the base address of the module can be different at different times,
   //   the base relocation data is necessary to make the module loadable
   //   at any address.
   IMAGE_BASE_RELOCATION *reloc = (IMAGE_BASE_RELOCATION *)GetPtrFromRVA(
      (DWORD)(ntHd->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress),
      ntHd,
      (PBYTE)dllBin);

   if(ntHd->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size)
      FixRelocs(dllBin,
         imageBase,
         ntHd,
         reloc,
         ntHd->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);

   //   Write the PE header into the remote process's memory space
   WriteProcessMemory(hProcess,
      imageBase,
      dllBin,
      ntHd->FileHeader.SizeOfOptionalHeader + sizeof(ntHd->FileHeader) + sizeof(ntHd->Signature),
      (SIZE_T *)&nBytes);

   //   Map the sections into the remote process(they need to be aligned
   //   along their virtual addresses)
   MapSections(hProcess, imageBase, dllBin, ntHd);

   //   Change the page protection on the DllCall_stub function from PAGE_EXECUTE_READ
   //   to PAGE_EXECUTE_READWRITE, so we can patch it.
   VirtualProtect((LPVOID)DllCall_stub,
      MakeDelta(SIZE_T, DC_stubend, DllCall_stub),
      PAGE_EXECUTE_READWRITE,
      (DWORD *)&nBytes);

   //   Patch the stub so it calls the correct address
   *MakePtr(unsigned long *, DllCall_stub, 9) =
      MakePtr(unsigned long, imageBase, ntHd->OptionalHeader.AddressOfEntryPoint);

   //   Write the stub into the remote process
   WriteProcessMemory(hProcess,
      stubBase,
      (LPVOID)DllCall_stub,
      MakeDelta(SIZE_T, DC_stubend, DllCall_stub),
      (SIZE_T *)&nBytes);

#ifdef __USING_DEBUGGER
   wxMessageBox(_("Calling CreateRemoteThread"));
   wxMessageBox( _("hProcess: ") + wxString::Format("%08X",hProcess) );
   wxMessageBox( _("stubBase: ") + wxString::Format("%08X",stubBase) );
   wxMessageBox( _("moduleBas: ") + wxString::Format("%08X",imageBase) );
#endif
   //   Execute our stub in the remote process
   CreateRemoteThread(hProcess,
      NULL,
      ntHd->OptionalHeader.SizeOfStackCommit,
      (LPTHREAD_START_ROUTINE)stubBase,
      imageBase,      //   Pass the base address of the module as the argument to the stub.
                       //   All a module handle is, is the base address of the module(except
                       //   in windows CE), so we're really passing a handle to the module
                       //   so that it can refer to itself, create dialogs, etc..
      0,
      NULL);

   delete dllBin;
   return true;
}