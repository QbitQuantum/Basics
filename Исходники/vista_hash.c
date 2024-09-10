int
main(int argc, char *argv[])
{
    byte *dll_1, *dll_2, *p1, *p2, *iat_start1, *iat_end1, *iat_start2, *iat_end2;
    bool has_iat = false;
    MEMORY_BASIC_INFORMATION info;
    void *drcontext = dr_standalone_init();
    uint writable_pages = 0, reserved_pages = 0, IAT_pages = 0;
    uint matched_pages = 0, second_matched_pages = 0, unmatched_pages = 0;
    uint exact_match_pages = 0, exact_no_match_pages = 0;
    char reloc_file[MAX_PATH] = {0}, orig_file[MAX_PATH], *input_file;
    uint old_size = 0, new_size = 0;
    uint old_base = 0, new_base = 0x69000000; /* unlikely to collide */

    /* user specified option defaults */
    uint arg_offs = 1;
    bool use_second_pass = true;
    bool assume_header_match = true;
    uint second_pass_offset = 16; /* FIXME arbitrary, what's a good choice? */
    bool assume_IAT_written = true;
    bool spin_for_debugger = false;

    if (argc < 2)
        return usage(argv[0]);
    while (argv[arg_offs][0] == '-') {
        if (strcmp(argv[arg_offs], "-vv") == 0) {
            vv = true;
        } else if (strcmp(argv[arg_offs], "-v") == 0) {
            v = true;
        } else if (strcmp(argv[arg_offs], "-no_second_pass") == 0) {
            use_second_pass = false;
        } else if (strcmp(argv[arg_offs], "-second_pass_offset") == 0) {
            if ((uint)argc <= arg_offs+1)
                return usage(argv[0]);
            second_pass_offset = atoi(argv[++arg_offs]);
        } else if (strcmp(argv[arg_offs], "-no_assume_IAT_written") == 0) {
            assume_IAT_written = false;
        } else if (strcmp(argv[arg_offs], "-spin_for_debugger") == 0) {
            spin_for_debugger = true;
        } else {
            return usage(argv[0]);
        }
        arg_offs++;
    }   
    input_file = argv[arg_offs++];
    if (arg_offs != argc)
        return usage(argv[0]);
    
    _snprintf(reloc_file, sizeof(reloc_file), "%s.reloc.dll", input_file);
    reloc_file[sizeof(reloc_file)-1] = '\0';
    if (!CopyFile(input_file, reloc_file, FALSE)) {
        LPSTR msg = NULL;
        uint error = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
                      0, GetLastError(), 0, msg, 0, NULL);
        VERBOSE_PRINT("Copy Error %d (0x%x) = %s\n", error, error, msg);
        return 1;
    }
    snprintf(orig_file, sizeof(orig_file), "%s.orig.dll", input_file);
    orig_file[sizeof(orig_file)-1] = '\0';
    if (!CopyFile(input_file, orig_file, FALSE)) {
        LPSTR msg = NULL;
        uint error = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
                      0, GetLastError(), 0, msg, 0, NULL);
        VERBOSE_PRINT("Copy Error %d (0x%x) = %s\n", error, error, msg);
        return 1;
    }
    if (ReBaseImage(reloc_file, "", TRUE, FALSE, FALSE, 0, &old_size, &old_base,
                    &new_size, &new_base, 0)) {
        VERBOSE_PRINT("Rebased imsage \"%s\" from 0x%08x to 0x%08x\n"
                      "Size changed from %d bytes to %d bytes\n",
                      input_file, old_base, new_base, old_size, new_size);
    } else {
        LPSTR msg = NULL;
        uint error = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
                      0, GetLastError(), 0, msg, 0, NULL);
        VERBOSE_PRINT("Rebase Error %d (0x%x) = %s\n", error, error, msg);
        return 1;
    }
    
    dll_1 = (byte *)ALIGN_BACKWARD(LoadLibraryExA(orig_file, NULL,
                                                  DONT_RESOLVE_DLL_REFERENCES),
                                   PAGE_SIZE);
    p1 = dll_1;
    dll_2 = (byte *)ALIGN_BACKWARD(LoadLibraryExA(reloc_file, NULL,
                                                  DONT_RESOLVE_DLL_REFERENCES),
                                   PAGE_SIZE);
    p2 = dll_2;
    VVERBOSE_PRINT("Loaded dll @ 0x%08x and 0x%08x\n", dll_1, dll_2);

    if (dll_1 == NULL || dll_2 == NULL) {
        VERBOSE_PRINT( "Error loading %s\n", input_file);
        return 1;
    }
    
    /* Handle the first page specially since I'm seeing problems with a handful of
     * dlls that aren't really getting rebased. mcupdate_GenuineIntel.dll for ex.
     * (which does have relocations etc.) not sure what's up, but it's only a couple of
     * dlls so will ignore them. If we really rebased the header should differ. */
    if (memcmp(dll_1, dll_2, PAGE_SIZE) == 0) {
        printf("%s - ERROR during relocating\n", input_file);
        return 1;
    } else {
        exact_no_match_pages++;
        if (assume_header_match)
            /* We could modify the hash function to catch header pages. */
            matched_pages++;
        else 
            unmatched_pages++;
    }
    p1 += PAGE_SIZE;
    p2 += PAGE_SIZE;

    if (assume_IAT_written && get_IAT_section_bounds(dll_1, &iat_start1, &iat_end1)) {
        has_iat = true;
        ASSERT(get_IAT_section_bounds(dll_2, &iat_start2, &iat_end2) &&
               iat_start1 - dll_1 == iat_start2 - dll_2 &&
               iat_end1 - dll_1 == iat_end2 - dll_2);
    }

    while (dr_virtual_query(p1, &info, sizeof(info)) == sizeof(info) &&
           info.State != MEM_FREE && info.AllocationBase == dll_1) {
        /* we only check read-only pages (assumption writable pages aren't shareable) */
        ASSERT(p1 == info.BaseAddress);
        if (info.State != MEM_COMMIT) {
            reserved_pages += info.RegionSize / PAGE_SIZE;
            VVERBOSE_PRINT("skipping %d reserved pages\n", info.RegionSize / PAGE_SIZE);
            p1 += info.RegionSize;
            p2 += info.RegionSize;
        } else if (!prot_is_writable(info.Protect)) {
            uint i;
            for (i = 0; i < info.RegionSize / PAGE_SIZE; i++) {
                bool exact = false;
                if (assume_IAT_written && has_iat &&
                    iat_end1 > p1 && iat_start1 < p1 + PAGE_SIZE) {
                    /* overlaps an IAT page */
                    IAT_pages++;
                    p1 += PAGE_SIZE;
                    p2 += PAGE_SIZE;
                    continue;
                }
                if (memcmp(p1, p2, PAGE_SIZE) == 0) {
                    VVERBOSE_PRINT("Page Exact Match\n");
                    exact_match_pages++;
                    exact = true;
                } else {
                    VVERBOSE_PRINT("Page Exact Mismatch\n");
                    exact_no_match_pages++;
                }
                if (compare_pages(drcontext, p1, p2, 0)) {
                    VVERBOSE_PRINT("Matched page\n");
                    matched_pages++;
                } else { 
                    VVERBOSE_PRINT("Failed to match page\n");
                    if (use_second_pass &&
                        compare_pages(drcontext, p1, p2, second_pass_offset)) {
                        second_matched_pages++;
                    } else {
                        unmatched_pages++;
                    }
                    ASSERT(!exact);
                }
                p1 += PAGE_SIZE;
                p2 += PAGE_SIZE;
            }
        } else {
            writable_pages += info.RegionSize / PAGE_SIZE;
            VVERBOSE_PRINT("skipping %d writable pages\n", info.RegionSize / PAGE_SIZE);
            p1 += info.RegionSize;
            p2 += info.RegionSize;
        }
    }

    VERBOSE_PRINT("%d exact match, %d not exact match\n%d hash_match, %d second_hash_match, %d hash_mismatch\n",
                  exact_match_pages, exact_no_match_pages, matched_pages, second_matched_pages, unmatched_pages); 

    printf("%s : %d pages - %d w %d res %d IAT = %d same %d differ : %d hash differ %d first hash differ : %d%% found, %d%% found first hash\n",
           input_file, writable_pages + reserved_pages + IAT_pages + exact_match_pages + exact_no_match_pages,
           writable_pages, reserved_pages, IAT_pages,
           exact_match_pages, exact_no_match_pages,
           unmatched_pages, unmatched_pages + second_matched_pages,
           (100 * (matched_pages + second_matched_pages - exact_match_pages))/exact_no_match_pages,
           (100 * (matched_pages - exact_match_pages))/exact_no_match_pages);

    while (spin_for_debugger)
        Sleep(1000);

    return 0;
}