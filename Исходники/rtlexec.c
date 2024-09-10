NTSTATUS
RtlCreateUserProcess(
    IN PUNICODE_STRING NtImagePathName,
    IN ULONG Attributes,
    IN PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    IN PSECURITY_DESCRIPTOR ProcessSecurityDescriptor OPTIONAL,
    IN PSECURITY_DESCRIPTOR ThreadSecurityDescriptor OPTIONAL,
    IN HANDLE ParentProcess OPTIONAL,
    IN BOOLEAN InheritHandles,
    IN HANDLE DebugPort OPTIONAL,
    IN HANDLE ExceptionPort OPTIONAL,
    OUT PRTL_USER_PROCESS_INFORMATION ProcessInformation
    )

/*++

Routine Description:

    This function creates a user mode process with a single thread with
    a suspend count of one.  The address space of the new process is
    initialized with the contents of specified image file.  The caller
    can specify the Access Control List for the new process and thread.
    The caller can also specify the parent process to inherit process
    priority and processor affinity from.  The default is to inherit
    these from the current process.  Finally the caller can specify
    whether the new process is to inherit any of the object handles
    from the specified parent process or not.

    Information about the new process and thread is returned via
    the ProcessInformation parameter.

Arguments:

    NtImagePathName - A required pointer that points to the NT Path string
        that identifies the image file that is to be loaded into the
        child process.

    ProcessParameters - A required pointer that points to parameters that
        are to passed to the child process.

    ProcessSecurityDescriptor - An optional pointer to the Security Descriptor
        give to the new process.

    ThreadSecurityDescriptor - An optional pointer to the Security Descriptor
        give to the new thread.

    ParentProcess - An optional process handle that will used to inherit
        certain properties from.

    InheritHandles - A boolean value.  TRUE specifies that object handles
        associated with the specified parent process are to be inherited
        by the new process, provided they have the OBJ_INHERIT attribute.
        FALSE specifies that the new process is to inherit no handles.

    DebugPort - An optional handle to the debug port associated with this
        process.

    ExceptionPort - An optional handle to the exception port associated with this
        process.

    ProcessInformation - A pointer to a variable that receives information
        about the new process and thread.

--*/

{
    NTSTATUS Status;
    HANDLE Section, File;
    OBJECT_ATTRIBUTES ObjectAttributes;
    PRTL_USER_PROCESS_PARAMETERS Parameters;
    SIZE_T ParameterLength;
    PVOID Environment;
    PWCHAR s;
    SIZE_T EnvironmentLength;
    SIZE_T RegionSize;
    PROCESS_BASIC_INFORMATION ProcessInfo;
    PPEB Peb;
    UNICODE_STRING Unicode;

    //
    // Zero output parameter and probe the addresses at the same time
    //

    RtlZeroMemory( ProcessInformation, sizeof( *ProcessInformation ) );
    ProcessInformation->Length = sizeof( *ProcessInformation );

    //
    // Open the specified image file.
    //

    Status = RtlpOpenImageFile( NtImagePathName,
                                Attributes & (OBJ_INHERIT | OBJ_CASE_INSENSITIVE),
                                &File,
                                TRUE
                              );
    if (!NT_SUCCESS( Status )) {
        return( Status );
        }


    //
    // Create a memory section backed by the opened image file
    //

    Status = ZwCreateSection( &Section,
                              SECTION_ALL_ACCESS,
                              NULL,
                              NULL,
                              PAGE_EXECUTE,
                              SEC_IMAGE,
                              File
                            );
    ZwClose( File );
    if ( !NT_SUCCESS( Status ) ) {
        return( Status );
        }


    //
    // Create the user mode process, defaulting the parent process to the
    // current process if one is not specified.  The new process will not
    // have a name nor will the handle be inherited by other processes.
    //

    if (!ARGUMENT_PRESENT( ParentProcess )) {
        ParentProcess = NtCurrentProcess();
        }

    InitializeObjectAttributes( &ObjectAttributes, NULL, 0, NULL,
                                ProcessSecurityDescriptor );
    if ( RtlGetNtGlobalFlags() & FLG_ENABLE_CSRDEBUG ) {
        if ( wcsstr(NtImagePathName->Buffer,L"csrss") ||
             wcsstr(NtImagePathName->Buffer,L"CSRSS")
           ) {

            //
            // For Hydra we don't name the CSRSS process to avoid name
            // collissions when multiple CSRSS's are started
            //
            if (ISTERMINALSERVER()) {

                InitializeObjectAttributes( &ObjectAttributes, NULL, 0, NULL,
                                            ProcessSecurityDescriptor );
            } else {

                RtlInitUnicodeString(&Unicode,L"\\WindowsSS");
                InitializeObjectAttributes( &ObjectAttributes, &Unicode, 0, NULL,
                                            ProcessSecurityDescriptor );
            }

            }
        }

    if ( !InheritHandles ) {
        ProcessParameters->CurrentDirectory.Handle = NULL;
        }
    Status = ZwCreateProcess( &ProcessInformation->Process,
                              PROCESS_ALL_ACCESS,
                              &ObjectAttributes,
                              ParentProcess,
                              InheritHandles,
                              Section,
                              DebugPort,
                              ExceptionPort
                            );
    if ( !NT_SUCCESS( Status ) ) {
        ZwClose( Section );
        return( Status );
        }


    //
    // Retrieve the interesting information from the image header
    //

    Status = ZwQuerySection( Section,
                             SectionImageInformation,
                             &ProcessInformation->ImageInformation,
                             sizeof( ProcessInformation->ImageInformation ),
                             NULL
                           );
    if ( !NT_SUCCESS( Status ) ) {
        ZwClose( ProcessInformation->Process );
        ZwClose( Section );
        return( Status );
        }

    Status = ZwQueryInformationProcess( ProcessInformation->Process,
                                        ProcessBasicInformation,
                                        &ProcessInfo,
                                        sizeof( ProcessInfo ),
                                        NULL
                                      );
    if ( !NT_SUCCESS( Status ) ) {
        ZwClose( ProcessInformation->Process );
        ZwClose( Section );
        return( Status );
        }

    Peb = ProcessInfo.PebBaseAddress;

    //
    // Duplicate Native handles into new process if any specified.
    // Note that the duplicated handles will overlay the input values.
    //

    try {
        Status = STATUS_SUCCESS;

        if ( ProcessParameters->StandardInput ) {

            Status = ZwDuplicateObject(
                        ParentProcess,
                        ProcessParameters->StandardInput,
                        ProcessInformation->Process,
                        &ProcessParameters->StandardInput,
                        0L,
                        0L,
                        DUPLICATE_SAME_ACCESS | DUPLICATE_SAME_ATTRIBUTES
                        );
            if ( !NT_SUCCESS(Status) ) {
                __leave;
            }
        }

        if ( ProcessParameters->StandardOutput ) {

            Status = ZwDuplicateObject(
                        ParentProcess,
                        ProcessParameters->StandardOutput,
                        ProcessInformation->Process,
                        &ProcessParameters->StandardOutput,
                        0L,
                        0L,
                        DUPLICATE_SAME_ACCESS | DUPLICATE_SAME_ATTRIBUTES
                        );
            if ( !NT_SUCCESS(Status) ) {
                __leave;
            }
        }

        if ( ProcessParameters->StandardError ) {

            Status = ZwDuplicateObject(
                        ParentProcess,
                        ProcessParameters->StandardError,
                        ProcessInformation->Process,
                        &ProcessParameters->StandardError,
                        0L,
                        0L,
                        DUPLICATE_SAME_ACCESS | DUPLICATE_SAME_ATTRIBUTES
                        );
            if ( !NT_SUCCESS(Status) ) {
                __leave;
            }
        }

    } finally {
        if ( !NT_SUCCESS(Status) ) {
            ZwClose( ProcessInformation->Process );
            ZwClose( Section );
        }
    }

    if ( !NT_SUCCESS(Status) ) {
        return Status;
    }

    //
    // Possibly reserve some address space in the new process
    //

    if (ProcessInformation->ImageInformation.SubSystemType == IMAGE_SUBSYSTEM_NATIVE ) {
        if ( ProcessParameters->Flags & RTL_USER_PROC_RESERVE_1MB ) {

            Environment = (PVOID)(4);
            RegionSize = (1024*1024)-(256);

            Status = ZwAllocateVirtualMemory( ProcessInformation->Process,
                                              (PVOID *)&Environment,
                                              0,
                                              &RegionSize,
                                              MEM_RESERVE,
                                              PAGE_READWRITE
                                            );
            if ( !NT_SUCCESS( Status ) ) {
                ZwClose( ProcessInformation->Process );
                ZwClose( Section );
                return( Status );
                }
            }
        }

    //
    // Allocate virtual memory in the new process and use NtWriteVirtualMemory
    // to write a copy of the process environment block into the address
    // space of the new process.  Save the address of the allocated block in
    // the process parameter block so the new process can access it.
    //

    if (s = (PWCHAR)ProcessParameters->Environment) {
        while (*s++) {
            while (*s++) {
                }
            }
        EnvironmentLength = (SIZE_T)(s - (PWCHAR)ProcessParameters->Environment) * sizeof(WCHAR);

        Environment = NULL;
        RegionSize = EnvironmentLength;
        Status = ZwAllocateVirtualMemory( ProcessInformation->Process,
                                          (PVOID *)&Environment,
                                          0,
                                          &RegionSize,
                                          MEM_COMMIT,
                                          PAGE_READWRITE
                                        );
        if ( !NT_SUCCESS( Status ) ) {
            ZwClose( ProcessInformation->Process );
            ZwClose( Section );
            return( Status );
            }

        Status = ZwWriteVirtualMemory( ProcessInformation->Process,
                                       Environment,
                                       ProcessParameters->Environment,
                                       EnvironmentLength,
                                       NULL
                                     );
        if ( !NT_SUCCESS( Status ) ) {
            ZwClose( ProcessInformation->Process );
            ZwClose( Section );
            return( Status );
            }

        ProcessParameters->Environment = Environment;
        }

    //
    // Allocate virtual memory in the new process and use NtWriteVirtualMemory
    // to write a copy of the process parameters block into the address
    // space of the new process.  Set the initial parameter to the new thread
    // to be the address of the block in the new process's address space.
    //

    Parameters = NULL;
    ParameterLength = ProcessParameters->MaximumLength;
    Status = ZwAllocateVirtualMemory( ProcessInformation->Process,
                                      (PVOID *)&Parameters,
                                      0,
                                      &ParameterLength,
                                      MEM_COMMIT,
                                      PAGE_READWRITE
                                    );
    if ( !NT_SUCCESS( Status ) ) {
        ZwClose( ProcessInformation->Process );
        ZwClose( Section );
        return( Status );
        }

    Status = ZwWriteVirtualMemory( ProcessInformation->Process,
                                   Parameters,
                                   ProcessParameters,
                                   ProcessParameters->Length,
                                   NULL
                                 );
    if ( !NT_SUCCESS( Status ) ) {
            ZwClose( ProcessInformation->Process );
            ZwClose( Section );
            return( Status );
            }

    Status = ZwWriteVirtualMemory( ProcessInformation->Process,
                                   &Peb->ProcessParameters,
                                   &Parameters,
                                   sizeof( Parameters ),
                                   NULL
                                 );
    if ( !NT_SUCCESS( Status ) ) {
        ZwClose( ProcessInformation->Process );
        ZwClose( Section );
        return( Status );
        }

    //
    // Create a suspended thread in the new process.  Specify the size and
    // position of the stack, along with the start address, initial parameter
    // and an SECURITY_DESCRIPTOR.  The new thread will not have a name and its handle will
    // not be inherited by other processes.
    //

    Status = RtlCreateUserThread(
                 ProcessInformation->Process,
                 ThreadSecurityDescriptor,
                 TRUE,
                 ProcessInformation->ImageInformation.ZeroBits,
                 ProcessInformation->ImageInformation.MaximumStackSize,
                 ProcessInformation->ImageInformation.CommittedStackSize,
                 (PUSER_THREAD_START_ROUTINE)
                     ProcessInformation->ImageInformation.TransferAddress,
                 (PVOID)Peb,
                 &ProcessInformation->Thread,
                 &ProcessInformation->ClientId
                 );
    if ( !NT_SUCCESS( Status ) ) {
        ZwClose( ProcessInformation->Process );
        ZwClose( Section );
        return( Status );
        }

    //
    // Now close the section and file handles.  The objects they represent
    // will not actually go away until the process is destroyed.
    //

    ZwClose( Section );

    //
    // Return success status
    //

    return( STATUS_SUCCESS );
}