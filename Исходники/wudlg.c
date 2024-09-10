ULONG FASTCALL WU32SysErrorBox(PVDMFRAME pFrame)
{
    DWORD dwExitCode;
    PSZ pszText;
    PSZ pszCaption;
    register PSYSERRORBOX16 parg16;

    GETARGPTR(pFrame, sizeof(SYSERRORBOX16), parg16);

    // WARNING - If things go wrong during boot, this routine can be called in
    // real mode (v86 mode).   So be very careful which GetPtr routines you
    // use to convert from 16:16 to flat pointers

    pszText = WOWGetVDMPointer(FETCHDWORD(parg16->vpszText),0,fWowMode);
    pszCaption = WOWGetVDMPointer(FETCHDWORD(parg16->vpszCaption),0,fWowMode);

    LOGDEBUG(5,("    SYSERRORBOX: %s\n", pszText));

    dwExitCode = WOWSysErrorBox(
                     pszCaption,
                     pszText,
                     parg16->sBtn1,
                     parg16->sBtn2,
                     parg16->sBtn3
                     );

    FREEPSZPTR(pszCaption);
    FREEPSZPTR(pszText);
    FREEARGPTR(parg16);
    RETURN(dwExitCode);
}