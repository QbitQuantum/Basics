ULONG FASTCALL WG32CreateDIBSection(PVDMFRAME pFrame)
{
    ULONG              ul = 0;
    STACKBMI32         bmi32;
    LPBITMAPINFO       lpbmi32;
    HBITMAP            hbm32;
    PVOID              pv16, pvBits, pvIntelBits;
    PVPVOID            vpbmi16;
    PVOID              pvBits32;
    DWORD              dwArg16;

    register PCREATEDIBSECTION16 parg16;

    GETARGPTR(pFrame, sizeof(CREATEDIBSECTION16), parg16);

    // this is performance hack so we don't generate extra code
    dwArg16 = FETCHDWORD(parg16->f4); // do it once here
    pv16 = (PVOID)GetPModeVDMPointer(dwArg16, sizeof(DWORD)); // aligned here!

    WOW32ASSERTMSG(((parg16->f5 == 0) && (parg16->f6 == 0)),
                   ("WOW:WG32CreateDIBSection, hSection/dwOffset non-null\n"));

    vpbmi16 = (PVPVOID)FETCHDWORD(parg16->f2);
    lpbmi32 = CopyBMI16ToBMI32(vpbmi16,
                               (LPBITMAPINFO)&bmi32,
                               FETCHWORD(parg16->f3));

    hbm32 = CreateDIBSection(HDC32(parg16->f1),
                             lpbmi32,
                             WORD32(parg16->f3),
                             &pvBits,
                             NULL,
                             0);

    if (hbm32 != 0)
    {
        PARM16          Parm16;
        PDIBSECTIONINFO pdi;
        ULONG           SelectorLimit;

        SelectorLimit = (ULONG)cjBitmapBitsSize(lpbmi32);
#ifndef i386
        if (!NT_SUCCESS(VdmAddVirtualMemory((ULONG)pvBits,
                                            SelectorLimit,
                                            (PULONG)&pvIntelBits))) {
            LOGDEBUG(LOG_ALWAYS,("\nWOW::WG32CreateDibSection VdmAddVirtualMemory failed\n"));
            goto cds_err;
        }

#else
        pvIntelBits = pvBits;
#endif

        // Create a selector array for the bits backed by pvIntelBits

        Parm16.WndProc.wParam = (WORD)-1;           // -1 => allocate selectors
        Parm16.WndProc.lParam = (LONG) pvIntelBits; // backing pointer
        Parm16.WndProc.wMsg = 0x10;                 // GA_NOCOMPACT
        Parm16.WndProc.hwnd = (WORD)((SelectorLimit+65535)/65536);// selector count

        CallBack16(RET_SETDIBSEL,
                   &Parm16,
                   0,
                   (PVPVOID)&pvBits32);

        // 16:16 pointer is still valid as call above makes no difference
        if (pv16 != NULL) {
            *(UNALIGNED PVOID*)pv16 = pvBits32;
        }

        if (pvBits32 == NULL) {
            LOGDEBUG(LOG_ALWAYS,("\nWOW::WG32CreateDibSection, Callback set_sel_for_dib failed\n"));
            goto cds_err;
        }

#ifndef i386 
        // okay, that was successful - map the descriptors properly

        if (!VdmAddDescriptorMapping(HIWORD(pvBits32),
                                    (USHORT) ((SelectorLimit+65535)/65536),
                                    (ULONG) pvIntelBits,
                                    (ULONG) pvBits)) {
            LOGDEBUG(LOG_ALWAYS,("\nWOW::WG32CreateDibSection VdmAddDescriptorMapping failed\n"));
            goto cds_err;
        }
#endif
        
        LOGDEBUG(LOG_ALWAYS, ("\nWOW:CreateDIBSection: [16:16 %x] [Intel %x] [Flat %x]\n", 
                             pvBits32, pvIntelBits, pvBits));

        ul = GETHBITMAP16(hbm32);

        // Add it to the list used for cleanup at DeleteObject time.

        if ((pdi = malloc_w (sizeof (DIBSECTIONINFO))) != NULL) {
            pdi->di_hbm         = (HBITMAP)(HAND16)hbm32;
            pdi->di_pv16        = pvBits32;
#ifndef i386
            pdi->di_newIntelDib = pvIntelBits;
#endif
            pdi->di_next        = pDibSectionInfoHead;
            pDibSectionInfoHead = pdi;

            // need to turn batching off since a DIBSECTION means the app can
            // also draw on the bitmap and we need synchronization.

            GdiSetBatchLimit(1);

            goto cds_ok;
        }
        else {
            // Failure, free the selector array

            Parm16.WndProc.wParam = (WORD)-1;            // -1 => allocate/free
            Parm16.WndProc.lParam = (LONG) pvBits32; // pointer
            Parm16.WndProc.wMsg = 0x10; // GA_NOCOMPACT
            Parm16.WndProc.hwnd = 0;                     // 0 => free

            CallBack16(RET_SETDIBSEL,
                       &Parm16,
                       0,
                       (PVPVOID)&ul);
#ifndef i386
            VdmRemoveVirtualMemory((ULONG)pvIntelBits);
#endif

        }
    }
    else {
        LOGDEBUG(LOG_ALWAYS,("\nWOW::WG32CreateDibSection, CreateDibSection Failed\n"));
    }

cds_err:

    if (hbm32 != 0) {
        DeleteObject(hbm32);
    }
    LOGDEBUG(LOG_ALWAYS,("\nWOW::WG32CreateDibSection returning failure\n"));
    ul = 0;

cds_ok:
    WOW32APIWARN(ul, "CreateDIBSection");

    FREEMISCPTR(pv16);
    FREEARGPTR(parg16);

    return(ul);
}