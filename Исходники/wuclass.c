ULONG FASTCALL WU32SetClassWord(PVDMFRAME pFrame)
{
    ULONG  ul, flag;
    HWND   hwnd;
    INT    iOffset;
    register PSETCLASSWORD16 parg16;

    GETARGPTR(pFrame, sizeof(SETCLASSWORD16), parg16);

    // Make sure Win32 didn't change offsets

#if (GCL_HBRBACKGROUND != (-10) || GCL_HCURSOR != (-12) || GCL_HICON != (-14) || GCL_CBWNDEXTRA != (-18) || GCL_CBCLSEXTRA != (-20) || GCL_STYLE != (-26))
#error Win16/Win32 GCW constants differ
#endif

    // Make sure the 16-bit app is requesting allowable offsets
    // (It's just assertion code, so it doesn't have to be pretty! -JTP)

    iOffset = INT32(parg16->f2);
    WOW32ASSERT(iOffset >= 0 ||
        iOffset == GCL_HBRBACKGROUND ||
        iOffset == GCL_HCURSOR ||
        iOffset == GCL_HICON ||
        iOffset == GCL_CBWNDEXTRA ||
        iOffset == GCL_CBCLSEXTRA ||
        iOffset == GCL_STYLE)

    hwnd = HWND32(parg16->f1);
    ul = WORD32(parg16->f3);

    switch(iOffset) {
        case GCL_HBRBACKGROUND:
            if (ul > COLOR_ENDCOLORS)
                ul = (LONG) HBRUSH32(ul);

            ul = SetClassLong(hwnd, iOffset, (LONG) ul);

            if (ul > COLOR_ENDCOLORS)
                ul = GETHBRUSH16(ul);
            break;

        case GCL_HCURSOR:
            ul = GETHCURSOR16(SetClassLong(hwnd, iOffset, (LONG)HCURSOR32(ul)));
            break;

        case GCL_HICON:
            ul = GETHICON16(SetClassLong(hwnd, iOffset, (LONG)HICON32(ul)));
            break;

        case GCL_HMODULE:
            ul = 0;         // not allowed to set this
            break;

        case GCL_CBWNDEXTRA:
        case GCL_STYLE:
            ul = SetClassLong(hwnd, iOffset, (LONG)ul);
            break;

        case GCL_CBCLSEXTRA:
            // apps shouldn't do this but of course some do!
            // (see GCW_CBCLSEXTRA notes in thunk for RegisterClass())
            WOW32WARNMSG(0, ("WOW:SetClassWord(): app changing cbClsExtra!"));

            // only allow this to be set by classes registered via WOW
            if(GetClassLong(hwnd, GCL_WNDPROC) & WNDPROC_WOW) { 

                // set the bozo flag 
                iOffset = GetClassLong(hwnd, GCL_CBCLSEXTRA);
                iOffset -= sizeof(DWORD);
                flag = SetClassLong(hwnd, iOffset, 1);

                // save the value the app passed 
                iOffset -= sizeof(DWORD);
                ul      = (WORD)SetClassWord(hwnd, iOffset, LOWORD(ul));

                // SetClassWord() returns the "previous" value.
                // if this is the first time the app pulls this stunt it will
                // get back the original cbClsExtra, otherwise it will get back
                // the value it stored here on the previous call.
                if(!flag) {
                    ul = iOffset; // the WOW DWORDs have already been subtracted
                }
            }
            else {
                ul = 0;  // no can do for non-WOW classes
            }
            break;

        default:
            ul = SetClassWord(hwnd, iOffset, (WORD)ul);
            break;
    }

    FREEARGPTR(parg16);
    RETURN(ul);
}