/**********************************************************************
 *			PE_LoadImage
 * Load one PE format DLL/EXE into memory
 *
 * Unluckily we can't just mmap the sections where we want them, for
 * (at least) Linux does only support offsets which are page-aligned.
 *
 * BUT we have to map the whole image anyway, for Win32 programs sometimes
 * want to access them. (HMODULE32 point to the start of it)
 */
HMODULE
PE_LoadImage (int handle, LPCSTR filename, WORD * version)
{
  HMODULE hModule;
  HANDLE mapping;

  IMAGE_NT_HEADERS *nt;
  IMAGE_SECTION_HEADER *pe_sec;
  IMAGE_DATA_DIRECTORY *dir;
  /* BY_HANDLE_FILE_INFORMATION bhfi; -- unused */
  int i, rawsize, lowest_va, vma_size, file_size = 0;
  DWORD load_addr = 0, aoep, reloc = 0;
  //struct get_read_fd_request *req = get_req_buffer();
  int unix_handle = handle;
  int page_size = getpagesize ();


  //if ( GetFileInformationByHandle( hFile, &bhfi ) )
  //  file_size = bhfi.nFileSizeLow;
  file_size = lseek (handle, 0, SEEK_END);
  lseek (handle, 0, SEEK_SET);

  //#warning fix CreateFileMappingA
  mapping = CreateFileMappingA (handle, NULL, PAGE_READONLY | SEC_COMMIT,
      0, 0, NULL);
  if (!mapping) {
    WARN ("CreateFileMapping error %ld\n", GetLastError ());
    return 0;
  }
  //hModule = (HMODULE)MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, 0 );
  hModule = (HMODULE) mapping;
  //CloseHandle( mapping );
  if (!hModule) {
    WARN ("MapViewOfFile error %ld\n", GetLastError ());
    return 0;
  }
  if (*(WORD *) hModule != IMAGE_DOS_SIGNATURE) {
    WARN ("%s image doesn't have DOS signature, but 0x%04x\n", filename,
        *(WORD *) hModule);
    goto error;
  }

  nt = PE_HEADER (hModule);


  if (nt->Signature != IMAGE_NT_SIGNATURE) {
    WARN ("%s image doesn't have PE signature, but 0x%08lx\n", filename,
        nt->Signature);
    goto error;
  }


  if (nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386) {
    MESSAGE ("Trying to load PE image for unsupported architecture (");
    switch (nt->FileHeader.Machine) {
      case IMAGE_FILE_MACHINE_UNKNOWN:
        MESSAGE ("Unknown");
        break;
      case IMAGE_FILE_MACHINE_I860:
        MESSAGE ("I860");
        break;
      case IMAGE_FILE_MACHINE_R3000:
        MESSAGE ("R3000");
        break;
      case IMAGE_FILE_MACHINE_R4000:
        MESSAGE ("R4000");
        break;
      case IMAGE_FILE_MACHINE_R10000:
        MESSAGE ("R10000");
        break;
      case IMAGE_FILE_MACHINE_ALPHA:
        MESSAGE ("Alpha");
        break;
      case IMAGE_FILE_MACHINE_POWERPC:
        MESSAGE ("PowerPC");
        break;
      default:
        MESSAGE ("Unknown-%04x", nt->FileHeader.Machine);
        break;
    }
    MESSAGE (")\n");
    goto error;
  }


  pe_sec = PE_SECTIONS (hModule);
  rawsize = 0;
  lowest_va = 0x10000;
  for (i = 0; i < nt->FileHeader.NumberOfSections; i++) {
    if (lowest_va > pe_sec[i].VirtualAddress)
      lowest_va = pe_sec[i].VirtualAddress;
    if (pe_sec[i].Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
      continue;
    if (pe_sec[i].PointerToRawData + pe_sec[i].SizeOfRawData > rawsize)
      rawsize = pe_sec[i].PointerToRawData + pe_sec[i].SizeOfRawData;
  }


  if (file_size && file_size < rawsize) {
    ERR ("PE module is too small (header: %d, filesize: %d), "
        "probably truncated download?\n", rawsize, file_size);
    goto error;
  }


  aoep = nt->OptionalHeader.AddressOfEntryPoint;
  if (aoep && (aoep < lowest_va))
    FIXME ("VIRUS WARNING: '%s' has an invalid entrypoint (0x%08lx) "
        "below the first virtual address (0x%08x) "
        "(possibly infected by Tchernobyl/SpaceFiller virus)!\n",
        filename, aoep, lowest_va);


  /* FIXME:  Hack!  While we don't really support shared sections yet,
   *         this checks for those special cases where the whole DLL
   *         consists only of shared sections and is mapped into the
   *         shared address space > 2GB.  In this case, we assume that
   *         the module got mapped at its base address. Thus we simply
   *         check whether the module has actually been mapped there
   *         and use it, if so.  This is needed to get Win95 USER32.DLL
   *         to work (until we support shared sections properly).
   */

  if (nt->OptionalHeader.ImageBase & 0x80000000) {
    HMODULE sharedMod = (HMODULE) nt->OptionalHeader.ImageBase;
    IMAGE_NT_HEADERS *sharedNt = (PIMAGE_NT_HEADERS)
        ((LPBYTE) sharedMod + ((LPBYTE) nt - (LPBYTE) hModule));

    /* Well, this check is not really comprehensive,
       but should be good enough for now ... */
    if (!IsBadReadPtr ((LPBYTE) sharedMod, sizeof (IMAGE_DOS_HEADER))
        && memcmp ((LPBYTE) sharedMod, (LPBYTE) hModule,
            sizeof (IMAGE_DOS_HEADER)) == 0
        && !IsBadReadPtr (sharedNt, sizeof (IMAGE_NT_HEADERS))
        && memcmp (sharedNt, nt, sizeof (IMAGE_NT_HEADERS)) == 0) {
      UnmapViewOfFile ((LPVOID) hModule);
      return sharedMod;
    }
  }



  load_addr = nt->OptionalHeader.ImageBase;
  vma_size = calc_vma_size (hModule);

  load_addr = (DWORD) VirtualAlloc ((void *) load_addr, vma_size,
      MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if (load_addr == 0) {

    //FIXME("We need to perform base relocations for %s\n", filename);
    dir = nt->OptionalHeader.DataDirectory + IMAGE_DIRECTORY_ENTRY_BASERELOC;
    if (dir->Size)
      reloc = dir->VirtualAddress;
    else {
      FIXME
          ("FATAL: Need to relocate %s, but no relocation records present (%s). Try to run that file directly !\n",
          filename,
          (nt->FileHeader.Characteristics & IMAGE_FILE_RELOCS_STRIPPED) ?
          "stripped during link" : "unknown reason");
      goto error;
    }

    /* FIXME: If we need to relocate a system DLL (base > 2GB) we should
     *        really make sure that the *new* base address is also > 2GB.
     *        Some DLLs really check the MSB of the module handle :-/
     */
    if (nt->OptionalHeader.ImageBase & 0x80000000)
      ERR ("Forced to relocate system DLL (base > 2GB). This is not good.\n");

    load_addr = (DWORD) VirtualAlloc (NULL, vma_size,
        MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!load_addr) {
      FIXME_ (win32)
          ("FATAL: Couldn't load module %s (out of memory, %d needed)!\n",
          filename, vma_size);
      goto error;
    }
  }

/*
    TRACE("Load addr is %lx (base %lx), range %x\n",
          load_addr, nt->OptionalHeader.ImageBase, vma_size );
    TRACE_(segment)("Loading %s at %lx, range %x\n",
                    filename, load_addr, vma_size );
*/
#if 0

  *(PIMAGE_DOS_HEADER) load_addr = *(PIMAGE_DOS_HEADER) hModule;
  *PE_HEADER (load_addr) = *nt;
  memcpy (PE_SECTIONS (load_addr), PE_SECTIONS (hModule),
      sizeof (IMAGE_SECTION_HEADER) * nt->FileHeader.NumberOfSections);


  memcpy (load_addr, hModule, lowest_fa);
#endif

  if ((void *) FILE_dommap (handle, (void *) load_addr, 0,
          nt->OptionalHeader.SizeOfHeaders, 0, 0,
          PROT_EXEC | PROT_WRITE | PROT_READ,
          MAP_PRIVATE | MAP_FIXED) != (void *) load_addr) {
    ERR_ (win32)
        ("Critical Error: failed to map PE header to necessary address.\n");
    goto error;
  }


  pe_sec = PE_SECTIONS (hModule);
  for (i = 0; i < nt->FileHeader.NumberOfSections; i++, pe_sec++) {
    if (!pe_sec->SizeOfRawData || !pe_sec->PointerToRawData)
      continue;
    /*
       TRACE("%s: mmaping section %s at %p off %lx size %lx/%lx\n",
       filename, pe_sec->Name, (void*)RVA(pe_sec->VirtualAddress),
       pe_sec->PointerToRawData, pe_sec->SizeOfRawData, pe_sec->Misc.VirtualSize );
     */
    if ((void *) FILE_dommap (unix_handle,
            (void *) RVA (pe_sec->VirtualAddress), 0, pe_sec->SizeOfRawData, 0,
            pe_sec->PointerToRawData, PROT_EXEC | PROT_WRITE | PROT_READ,
            MAP_PRIVATE | MAP_FIXED) != (void *) RVA (pe_sec->VirtualAddress)) {
      ERR_ (win32)
          ("Critical Error: failed to map PE section to necessary address.\n");
      goto error;
    }
    if ((pe_sec->SizeOfRawData < pe_sec->Misc.VirtualSize) &&
        (pe_sec->SizeOfRawData & (page_size - 1))) {
      DWORD end = (pe_sec->SizeOfRawData & ~(page_size - 1)) + page_size;
      if (end > pe_sec->Misc.VirtualSize)
        end = pe_sec->Misc.VirtualSize;
      TRACE ("clearing %p - %p\n",
          (char *) RVA (pe_sec->VirtualAddress) + pe_sec->SizeOfRawData,
          (char *) RVA (pe_sec->VirtualAddress) + end);
      memset ((char *) RVA (pe_sec->VirtualAddress) + pe_sec->SizeOfRawData, 0,
          end - pe_sec->SizeOfRawData);
    }
  }


  if (reloc)
    do_relocations (load_addr, (IMAGE_BASE_RELOCATION *) RVA (reloc));


  *version = ((nt->OptionalHeader.MajorSubsystemVersion & 0xff) << 8)
      | (nt->OptionalHeader.MinorSubsystemVersion & 0xff);


  UnmapViewOfFile ((LPVOID) hModule);
  return (HMODULE) load_addr;

error:
  if (unix_handle != -1)
    close (unix_handle);
  if (load_addr)
    VirtualFree ((LPVOID) load_addr, 0, MEM_RELEASE);
  UnmapViewOfFile ((LPVOID) hModule);
  return 0;
}