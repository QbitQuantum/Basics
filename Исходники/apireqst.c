PCSR_THREAD CsrConnectToUser( VOID )
{
    static BOOLEAN (*ClientThreadSetupRoutine)(VOID) = NULL;
    NTSTATUS Status;
    ANSI_STRING DllName;
    UNICODE_STRING DllName_U;
    STRING ProcedureName;
    HANDLE UserClientModuleHandle;
    PTEB Teb;
    PCSR_THREAD Thread;
    BOOLEAN fConnected;

    if (ClientThreadSetupRoutine == NULL) {
        RtlInitAnsiString(&DllName, "user32");
        Status = RtlAnsiStringToUnicodeString(&DllName_U, &DllName, TRUE);
        ASSERT(NT_SUCCESS(Status));
        Status = LdrGetDllHandle(
                    UNICODE_NULL,
                    NULL,
                    &DllName_U,
                    (PVOID *)&UserClientModuleHandle
                    );

        RtlFreeUnicodeString(&DllName_U);

        if ( NT_SUCCESS(Status) ) {
            RtlInitString(&ProcedureName,"ClientThreadSetup");
            Status = LdrGetProcedureAddress(
                            UserClientModuleHandle,
                            &ProcedureName,
                            0L,
                            (PVOID *)&ClientThreadSetupRoutine
                            );
            ASSERT(NT_SUCCESS(Status));
        }
    }

    try {
        fConnected = ClientThreadSetupRoutine();
    } except (EXCEPTION_EXECUTE_HANDLER) {
        fConnected = FALSE;
    }
    if (!fConnected) {
            IF_DEBUG {
            DbgPrint("CSRSS: CsrConnectToUser failed\n");
                }
        return NULL;
    }