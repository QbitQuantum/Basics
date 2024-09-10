static void
process_exports(void *dcontext, char *dllname)
{
    LOADED_IMAGE img;
    IMAGE_EXPORT_DIRECTORY *dir;
    IMAGE_SECTION_HEADER *sec;
    DWORD *name, *code;
    WORD *ordinal;
    const char *string;
    uint size;
    BOOL res;
    uint i;
    byte *addr, *start_exports, *end_exports;

    verbose_print("Processing exports of \"%s\"\n", dllname);
    res = MapAndLoad(dllname, NULL, &img, FALSE, TRUE);
    if (!res) {
        print("Error loading %s\n", dllname);
        return;
    }
    dir = (IMAGE_EXPORT_DIRECTORY *)
        ImageDirectoryEntryToData(img.MappedAddress, FALSE,
                                  IMAGE_DIRECTORY_ENTRY_EXPORT, &size);
    verbose_print("mapped at 0x%08x, exports is at 0x%08x, size is 0x%x\n",
                  img.MappedAddress, dir, size);
    start_exports = (byte *) dir;
    end_exports = start_exports + size;
    verbose_print("name=%s, ord base=0x%08x, names=%d 0x%08x\n",
                  (char *) ImageRvaToVa(img.FileHeader, img.MappedAddress,
                                        dir->Name, NULL),
                  dir->Base, dir->NumberOfNames, dir->AddressOfNames);

    /* don't limit functions to lie in .text -- 
     * for ntdll, some exported routines have their code after .text, inside
     * ECODE section!
     */
    sec = img.Sections;
    for (i = 0; i < img.NumberOfSections; i++) {
        verbose_print("Section %d %s: 0x%x + 0x%x == 0x%08x through 0x%08x\n",
                      i, sec->Name, sec->VirtualAddress, sec->SizeOfRawData,
                      ImageRvaToVa(img.FileHeader, img.MappedAddress,
                                   sec->VirtualAddress, NULL),
                      (uint) ImageRvaToVa(img.FileHeader, img.MappedAddress,
                                          sec->VirtualAddress, NULL) +
                      sec->SizeOfRawData);
        sec++;
    }

    name = (DWORD *) ImageRvaToVa(img.FileHeader, img.MappedAddress,
                                  dir->AddressOfNames, NULL);
    code = (DWORD *) ImageRvaToVa(img.FileHeader, img.MappedAddress,
                                  dir->AddressOfFunctions, NULL);
    ordinal = (WORD *) ImageRvaToVa(img.FileHeader, img.MappedAddress,
                                    dir->AddressOfNameOrdinals, NULL);
    verbose_print("names: from 0x%08x to 0x%08x\n",
                  ImageRvaToVa(img.FileHeader, img.MappedAddress, name[0], NULL),
                  ImageRvaToVa(img.FileHeader, img.MappedAddress,
                               name[dir->NumberOfNames-1], NULL));

    for (i = 0; i < dir->NumberOfNames; i++) {
        string = (char *) ImageRvaToVa(img.FileHeader, img.MappedAddress, name[i], NULL);
        /* ordinal is biased (dir->Base), but don't add base when using as index */
        assert(dir->NumberOfFunctions > ordinal[i]);
        /* I don't understand why have to do RVA to VA here, when dumpbin /exports
         * seems to give the same offsets but by simply adding them to base we
         * get the appropriate code location -- but that doesn't work here...
         */
        addr = ImageRvaToVa(img.FileHeader, img.MappedAddress,
                            code[ordinal[i]], NULL);
        verbose_print("name=%s 0x%08x, ord=%d, code=0x%x -> 0x%08x\n",
                      string, string, ordinal[i], code[ordinal[i]], addr);
        if (list_exports) {
            print("ord %3d offs 0x%08x %s\n", ordinal[i],
                  addr - img.MappedAddress, string);
        }
        if (list_Ki && string[0] == 'K' && string[1] == 'i') {
            print("\n==================================================\n");
            print("%s\n\n", string);
            check_Ki(string);
            print("\ndisassembly:\n");
            decode_function(dcontext, addr);
            print(  "==================================================\n");
        }
        /* forwarded export points inside exports section */
        if (addr >= start_exports && addr < end_exports) {
            if (list_forwards || verbose) {
                /* I've had issues w/ forwards before, so avoid printing crap */
                if (addr[0] > 0 && addr[0] < 127)
                    print("%s is forwarded to %.128s\n", string, addr);
                else
                    print("ERROR identifying forwarded entry for %s\n", string);
            }
        } else if (list_syscalls) {
            process_syscall_wrapper(dcontext, addr, string, "export");
        }
    }

    if (list_syscalls)
        process_symbols(dcontext, dllname, &img);

    UnMapAndLoad(&img);
}