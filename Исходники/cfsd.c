/* 
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= **
 *
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= **
 */
NTSTATUS
cfsd_UserModeCommunication( IN PVOID ConnectionCookie,
                            IN PVOID InputBuffer  OPTIONAL,
                            IN ULONG InputBufferSize,
                            OUT PVOID OutputBuffer OPTIONAL,
                            IN ULONG OutputBufferSize,
                            OUT PULONG ReturnOutputBufferLength )

{
STRING		   FNameString;


 KdPrint( (PRINT_TAG "File Name from USER MODE to hide (%s) [%d]\n", InputBuffer, InputBufferSize ) );

/*
!!!!!!!!!!!!!!!
ALL TEMP CODE SO YOU CAN TEST THE DRIVER FROM USER MODE WITHOUT HAVING TO RECOMPILE TO CHANGE A FILE NAME
!!!!!!!!!!!!!!
*/

  try 
  {
   RtlInitAnsiString( &FNameString, InputBuffer );

    RtlAnsiStringToUnicodeString( &uFName, &FNameString, TRUE );

    RtlUpcaseUnicodeString( &uFName, &uFName, FALSE );

    gHiddenData->HFile = uFName;

// By not calling this we are going to leak memory everytime user mode makes a file name change. This is just a kludge
// to let user mode experiement with file names
//	RtlFreeUnicodeString(&uFName);

  }
  except( EXCEPTION_EXECUTE_HANDLER ) 
  {
   return GetExceptionCode();
  }

 return STATUS_SUCCESS;
}