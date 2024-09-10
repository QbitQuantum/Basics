/* Dump out .data and .bss sections into a new executable.  */
void
unexec (const char *new_name, const char *old_name)
{
    file_data in_file, out_file;
    char out_filename[MAX_PATH], in_filename[MAX_PATH], new_name_a[MAX_PATH];
    unsigned long size;
    char *p;
    char *q;

    /* Ignore old_name, and get our actual location from the OS.  */
    if (!GetModuleFileNameA (NULL, in_filename, MAX_PATH))
        abort ();

    /* Can't use dostounix_filename here, since that needs its file name
       argument encoded in UTF-8.  */
    for (p = in_filename; *p; p = CharNextA (p))
        if (*p == '\\')
            *p = '/';

    strcpy (out_filename, in_filename);
    filename_to_ansi (new_name, new_name_a);

    /* Change the base of the output filename to match the requested name.  */
    if ((p = strrchr (out_filename, '/')) == NULL)
        abort ();
    /* The filenames have already been expanded, and will be in Unix
       format, so it is safe to expect an absolute name.  */
    if ((q = strrchr (new_name_a, '/')) == NULL)
        abort ();
    strcpy (p, q);

#ifdef ENABLE_CHECKING
    report_temacs_memory_usage ();
#endif

    /* Make sure that the output filename has the ".exe" extension...patch
       it up if not.  */
    p = out_filename + strlen (out_filename) - 4;
    if (strcmp (p, ".exe"))
        strcat (out_filename, ".exe");

    printf ("Dumping from %s\n", in_filename);
    printf ("          to %s\n", out_filename);

    /* Open the undumped executable file.  */
    if (!open_input_file (&in_file, in_filename))
    {
        printf ("Failed to open %s (%d)...bailing.\n",
                in_filename, GetLastError ());
        exit (1);
    }

    /* Get the interesting section info, like start and size of .bss...  */
    get_section_info (&in_file);

    /* The size of the dumped executable is the size of the original
       executable plus the size of the heap and the size of the .bss section.  */
    size = in_file.size +
           extra_bss_size +
           extra_bss_size_static;
    if (!open_output_file (&out_file, out_filename, size))
    {
        printf ("Failed to open %s (%d)...bailing.\n",
                out_filename, GetLastError ());
        exit (1);
    }

    /* Set the flag (before dumping).  */
    using_dynamic_heap = TRUE;

    copy_executable_and_dump_data (&in_file, &out_file);

    /* Unset it because it is plain wrong to keep it after dumping.
       Malloc can still occur!  */
    using_dynamic_heap = FALSE;

    /* Patch up header fields; profiler is picky about this. */
    {
        PIMAGE_DOS_HEADER dos_header;
        PIMAGE_NT_HEADERS nt_header;
        HANDLE hImagehelp = LoadLibrary ("imagehlp.dll");
        DWORD  headersum;
        DWORD  checksum;

        dos_header = (PIMAGE_DOS_HEADER) out_file.file_base;
        nt_header = (PIMAGE_NT_HEADERS) ((char *) dos_header + dos_header->e_lfanew);

        nt_header->OptionalHeader.CheckSum = 0;
//    nt_header->FileHeader.TimeDateStamp = time (NULL);
//    dos_header->e_cp = size / 512;
//    nt_header->OptionalHeader.SizeOfImage = size;

        pfnCheckSumMappedFile = (void *) GetProcAddress (hImagehelp, "CheckSumMappedFile");
        if (pfnCheckSumMappedFile)
        {
//	nt_header->FileHeader.TimeDateStamp = time (NULL);
            pfnCheckSumMappedFile (out_file.file_base,
                                   out_file.size,
                                   &headersum,
                                   &checksum);
            nt_header->OptionalHeader.CheckSum = checksum;
        }
        FreeLibrary (hImagehelp);
    }

    close_file_data (&in_file);
    close_file_data (&out_file);
}