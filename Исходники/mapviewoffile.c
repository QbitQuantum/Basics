int __cdecl main(int argc, char *argv[])
{

    const   int MAPPINGSIZE = 2048;
    HANDLE  hFileMapping;
    LPVOID  lpMapViewAddress;
    char *p;
    int i;

    /* Initialize the PAL environment.
     */
    if(0 != PAL_Initialize(argc, argv))
    {
        return FAIL;
    }

    hFileMapping = CreateFileMappingW(INVALID_HANDLE_VALUE,
                                      NULL,
                                      PAGE_READWRITE,
                                      0,
                                      MAPPINGSIZE,
                                      NULL);

    if (hFileMapping == NULL) {
        Trace("ERROR:%u: CreateFileMappingW() failed\n", GetLastError());
        Fail("");
    }


    lpMapViewAddress = MapViewOfFile(
                            hFileMapping,
                            FILE_MAP_WRITE, /* access code */
                            0,              /* high order offset */
                            0,              /* low order offset */
                            MAPPINGSIZE);   /* number of bytes for map */

    if(NULL == lpMapViewAddress)
    {
        Trace("ERROR:%u: MapViewOfFile() failed.\n",
              GetLastError());
        CloseHandle(hFileMapping);
        Fail("");
    }

    p = (char *)lpMapViewAddress;
    for (i=0; i<MAPPINGSIZE; ++i) {
        /* Confirm that the memory is zero-initialized */
        if (p[i] != 0) 
        {
            Fail("MapViewOfFile() of pagefile didn't return 0-filled data "
                 "(Offset %d has value 0x%x)\n", i, p[i]);
        }
        /* Confirm that it is writable */
        *(char *)lpMapViewAddress = 0xcc;
    }

    /* Clean-up and Terminate the PAL.
    */
    CloseHandle(hFileMapping);
    UnmapViewOfFile(lpMapViewAddress);
    PAL_Terminate();
    return PASS;
}