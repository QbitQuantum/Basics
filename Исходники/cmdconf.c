/* cmdGetAutoexecBat - Creates a temp file to replace c:\autoexec.bat
 *
 *  Entry - Client  (DS:DX)  pointer to receive file name
 *
 *  EXIT  - This routine will Terminate the vdm if it fails
 *          And will not return
 *
 *
 *  The buffer to receive the file name must be at least 64 bytes
 */
VOID cmdGetAutoexecBat (VOID)
{
     UNICODE_STRING Unicode;
     OEM_STRING     OemString;
     ANSI_STRING    AnsiString;

     ExpandConfigFiles(FALSE);

     RtlInitAnsiString(&AnsiString, pchTmpAutoexecFile);
     if (!NT_SUCCESS(RtlAnsiStringToUnicodeString(&Unicode,&AnsiString,TRUE)) )
         goto ErrExit;

     OemString.Buffer = (char *)GetVDMAddr(getDS(),getDX());
     OemString.MaximumLength = 64;
     if (!NT_SUCCESS(RtlUnicodeStringToOemString(&OemString,&Unicode,FALSE)) )
         goto ErrExit;

     RtlFreeUnicodeString(&Unicode);

     return;

ErrExit:
     RcErrorDialogBox(ED_INITMEMERR, pchTmpConfigFile, NULL);
     TerminateVDM();  // skip cleanup since I insist that we exit!
}