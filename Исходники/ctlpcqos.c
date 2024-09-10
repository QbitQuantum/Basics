VOID
SepServerSpawnClientProcess(VOID)

{


    RTL_USER_PROCESS_INFORMATION ProcessInformation;
    STRING ImagePathName, ProgramName;
    UNICODE_STRING UnicodeImagePathName, UnicodeProgramName;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;

    RtlInitString( &ProgramName, "\\SystemRoot\\Bin\\utlpcqos.exe" );
    Status = RtlAnsiStringToUnicodeString(
                 &UnicodeProgramName,
                 &ProgramName,
                 TRUE );  SEASSERT_SUCCESS( NT_SUCCESS(Status) );
    RtlInitString( &ImagePathName, "utlpcqos.exe");
    Status = RtlAnsiStringToUnicodeString(
                 &UnicodeImagePathName,
                 &ImagePathName,
                 TRUE );  SEASSERT_SUCCESS( NT_SUCCESS(Status) );

    Status = RtlCreateProcessParameters(
                 &ProcessParameters,
                 &ImagePathName,        //UNICODEFIX &UnicodeImagePathName,
                 NULL,
                 NULL,
                 NULL,
                 NULL,
                 NULL,
                 NULL,
                 NULL,
                 NULL
                 );

    SEASSERT_SUCCESS(Status);


    Status = RtlCreateUserProcess(
                 &ProgramName,                   // UNICODEFIX &UnicodeProgramName,
                 ProcessParameters,              // ProcessParameters
                 NULL,                           // ProcessSecurityDescriptor
                 NULL,                           // ThreadSecurityDescriptor
                 NtCurrentProcess(),             // ParentProcess
                 FALSE,                          // InheritHandles
                 NULL,                           // DebugPort
                 NULL,                           // ExceptionPort
                 &ProcessInformation             // ProcessInformation
                 ); SEASSERT_SUCCESS(Status);

    Status = NtResumeThread(
                  ProcessInformation.Thread,
                  NULL
                  ); SEASSERT_SUCCESS(Status);

    RtlDestroyProcessParameters( ProcessParameters );
    RtlFreeUnicodeString( &UnicodeProgramName );
    RtlFreeUnicodeString( &UnicodeImagePathName );

}