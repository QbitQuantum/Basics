/***********************************************************************
 *           GetCommandLineA      (KERNEL32.@)
 *
 * WARNING: there's a Windows incompatibility lurking here !
 * Win32s always includes the full path of the program file,
 * whereas Windows NT only returns the full file path plus arguments
 * in case the program has been started with a full path.
 * Win9x seems to have inherited NT behaviour.
 *
 * Note that both Start Menu Execute and Explorer start programs with
 * fully specified quoted app file paths, which is why probably the only case
 * where you'll see single file names is in case of direct launch
 * via CreateProcess or WinExec.
 *
 * Perhaps we should take care of Win3.1 programs here (Win32s "feature").
 *
 * References: MS KB article q102762.txt (special Win32s handling)
 */
LPSTR WINAPI GetCommandLineA(void)
{
    static char *cmdlineA;  /* ASCII command line */

    if (!cmdlineA) /* make an ansi version if we don't have it */
    {
        ANSI_STRING     ansi;
        RtlAcquirePebLock();

        cmdlineA = (RtlUnicodeStringToAnsiString( &ansi, &NtCurrentTeb()->Peb->ProcessParameters->CommandLine, TRUE) == STATUS_SUCCESS) ?
                   ansi.Buffer : NULL;
        RtlReleasePebLock();
    }
    return cmdlineA;
}