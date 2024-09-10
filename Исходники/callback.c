NTSTATUS TdProtectNameCallback (
    _In_ PTD_PROTECTNAME_INPUT pProtectName
)
{
    NTSTATUS Status = STATUS_SUCCESS;

    if (!pProtectName) {
        DbgPrintEx (
            DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL,
            "ObCallbackTest: TdProtectNameCallback: name to protect/filter NULL pointer\n"
        );
    }
    else {
        DbgPrintEx (
            DPFLTR_IHVDRIVER_ID, DPFLTR_TRACE_LEVEL,
            "ObCallbackTest: TdProtectNameCallback: entering name to protect/filter %ls\n", pProtectName->Name
        );
    }
    KeAcquireGuardedMutex (&TdCallbacksMutex);

    // Need to copy out the name and then set the flag to filter
    // This will allow process creation to watch for the process to be created and get the PID
    // and then prevent any other process from opening up that PID to terminate

    memcpy(TdwProtectName, pProtectName->Name, sizeof(TdwProtectName));

    DbgPrintEx (
        DPFLTR_IHVDRIVER_ID, DPFLTR_TRACE_LEVEL,
        "ObCallbackTest: name copied     %ls\n", TdwProtectName
    );

    // Need to enable the OB callbacks
    // once the process is matched to a newly created process, the callbacks will protect the process
    if (bCallbacksInstalled == FALSE) {
        DbgPrintEx (
            DPFLTR_IHVDRIVER_ID, DPFLTR_TRACE_LEVEL,
            "ObCallbackTest: TdProtectNameCallback: installing callbacks\n"
        );

        // Setup the Ob Registration calls

        CBOperationRegistrations[0].ObjectType = PsProcessType;
        CBOperationRegistrations[0].Operations |= OB_OPERATION_HANDLE_CREATE;
        CBOperationRegistrations[0].Operations |= OB_OPERATION_HANDLE_DUPLICATE;
        CBOperationRegistrations[0].PreOperation = CBTdPreOperationCallback;
        CBOperationRegistrations[0].PostOperation = CBTdPostOperationCallback;

        CBOperationRegistrations[1].ObjectType = PsThreadType;
        CBOperationRegistrations[1].Operations |= OB_OPERATION_HANDLE_CREATE;
        CBOperationRegistrations[1].Operations |= OB_OPERATION_HANDLE_DUPLICATE;
        CBOperationRegistrations[1].PreOperation = CBTdPreOperationCallback;
        CBOperationRegistrations[1].PostOperation = CBTdPostOperationCallback;


        RtlInitUnicodeString (&CBAltitude, L"1000");

        CBObRegistration.Version                    = OB_FLT_REGISTRATION_VERSION;
        CBObRegistration.OperationRegistrationCount = 2;
        CBObRegistration.Altitude                   = CBAltitude;
        CBObRegistration.RegistrationContext        = &CBCallbackRegistration;
        CBObRegistration.OperationRegistration      = CBOperationRegistrations;


        Status = ObRegisterCallbacks (
            &CBObRegistration,
            &pCBRegistrationHandle       // save the registration handle to remove callbacks later
        );

        if (!NT_SUCCESS (Status))   {
            DbgPrintEx (
                DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL,
                "ObCallbackTest: installing OB callbacks failed  status 0x%x\n", Status
            );
            KeReleaseGuardedMutex (&TdCallbacksMutex); // Release the lock before exit
            goto Exit;
        }
        bCallbacksInstalled = TRUE;

    }


    KeReleaseGuardedMutex (&TdCallbacksMutex);


    DbgPrintEx (
        DPFLTR_IHVDRIVER_ID, DPFLTR_TRACE_LEVEL,
        "ObCallbackTest: TdProtectNameCallback: name to protect/filter %ls\n", TdwProtectName
    );

Exit:
    DbgPrintEx (
        DPFLTR_IHVDRIVER_ID, DPFLTR_TRACE_LEVEL,
        "ObCallbackTest: TdProtectNameCallback: exiting  status 0x%x\n", Status
    );
    return Status;
}