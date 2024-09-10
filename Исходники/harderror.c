static
NTSTATUS
UserpFormatMessages(
    OUT PUNICODE_STRING TextStringU,
    OUT PUNICODE_STRING CaptionStringU,
    IN  PULONG_PTR Parameters,
    IN  ULONG SizeOfStrings,
    IN  PHARDERROR_MSG Message,
    IN  HANDLE hProcess)
{
    NTSTATUS Status;
    UNICODE_STRING FileNameU, TempStringU, FormatU;
    ANSI_STRING FormatA;
    PMESSAGE_RESOURCE_ENTRY MessageResource;
    PWSTR FormatString;
    ULONG Size, ExceptionCode;

    /* Get the file name of the client process */
    UserpGetClientFileName(&FileNameU, hProcess);

    /* Check if we have a file name */
    if (!FileNameU.Buffer)
    {
        /* No, use system */
        RtlInitUnicodeString(&FileNameU, L"System");
    }

    /* Get text string of the error code */
    Status = RtlFindMessage(GetModuleHandleW(L"ntdll"),
                            (ULONG_PTR)RT_MESSAGETABLE,
                            LANG_NEUTRAL,
                            Message->Status,
                            &MessageResource);

    if (NT_SUCCESS(Status))
    {
        if (MessageResource->Flags)
        {
            RtlInitUnicodeString(&FormatU, (PWSTR)MessageResource->Text);
            FormatA.Buffer = NULL;
        }
        else
        {
            RtlInitAnsiString(&FormatA, (PCHAR)MessageResource->Text);
            RtlAnsiStringToUnicodeString(&FormatU, &FormatA, TRUE);
        }
    }
    else
    {
        /* Fall back to hardcoded value */
        RtlInitUnicodeString(&FormatU, L"Unknown Hard Error");
        FormatA.Buffer = NULL;
    }

    FormatString = FormatU.Buffer;

    /* Check whether a caption exists */
    if (FormatString[0] == L'{')
    {
        /* Set caption start */
        TempStringU.Buffer = ++FormatString;

        /* Get size of the caption */
        for (Size = 0; *FormatString != 0 && *FormatString != L'}'; Size++)
            FormatString++;

        /* Skip '}', '\r', '\n' */
        FormatString += 3;

        TempStringU.Length = Size * sizeof(WCHAR);
        TempStringU.MaximumLength = TempStringU.Length;
    }
    else
    {
        /* FIXME: Set string based on severity */
        RtlInitUnicodeString(&TempStringU, L"Application Error");
    }

    /* Calculate buffer length for the caption */
    CaptionStringU->MaximumLength = FileNameU.Length + TempStringU.Length +
                                    4 * sizeof(WCHAR);

    /* Allocate a buffer for the caption */
    CaptionStringU->Buffer = RtlAllocateHeap(RtlGetProcessHeap(),
                             HEAP_ZERO_MEMORY,
                             CaptionStringU->MaximumLength);

    /* Append the file name, seperator and the caption text */
    CaptionStringU->Length = 0;
    RtlAppendUnicodeStringToString(CaptionStringU, &FileNameU);
    RtlAppendUnicodeToString(CaptionStringU, L" - ");
    RtlAppendUnicodeStringToString(CaptionStringU, &TempStringU);

    /* Zero terminate the buffer */
    CaptionStringU->Buffer[CaptionStringU->Length / sizeof(WCHAR)] = 0;

    /* Free the file name buffer */
    RtlFreeUnicodeString(&FileNameU);

    /* Check if this is an exception message */
    if (Message->Status == STATUS_UNHANDLED_EXCEPTION)
    {
        ExceptionCode = Parameters[0];

        /* Handle special cases */
        if (ExceptionCode == STATUS_ACCESS_VIOLATION)
        {
            Parameters[0] = Parameters[1];
            Parameters[1] = Parameters[3];
            if (Parameters[2]) Parameters[2] = (ULONG_PTR)L"written";
            else Parameters[2] = (ULONG_PTR)L"read";
            MessageResource = NULL;
        }
        else if (ExceptionCode == STATUS_IN_PAGE_ERROR)
        {
            Parameters[0] = Parameters[1];
            Parameters[1] = Parameters[3];
            MessageResource = NULL;
        }
        else
        {
            /* Fall back to hardcoded value */
            Parameters[2] = Parameters[1];
            Parameters[1] = Parameters[0];
            Parameters[0] = (ULONG_PTR)L"unknown software exception";
        }

        if (!MessageResource)
        {
            /* Get text string of the exception code */
            Status = RtlFindMessage(GetModuleHandleW(L"ntdll"),
                                    (ULONG_PTR)RT_MESSAGETABLE,
                                    LANG_NEUTRAL,
                                    ExceptionCode,
                                    &MessageResource);

            if (NT_SUCCESS(Status))
            {
                if (FormatA.Buffer) RtlFreeUnicodeString(&FormatU);

                if (MessageResource->Flags)
                {
                    RtlInitUnicodeString(&FormatU, (PWSTR)MessageResource->Text);
                    FormatA.Buffer = NULL;
                }
                else
                {
                    RtlInitAnsiString(&FormatA, (PCHAR)MessageResource->Text);
                    RtlAnsiStringToUnicodeString(&FormatU, &FormatA, TRUE);
                }
                FormatString = FormatU.Buffer;
            }
            else
            {
                /* Fall back to hardcoded value */
                Parameters[2] = Parameters[1];
                Parameters[1] = Parameters[0];
                Parameters[0] = (ULONG_PTR)L"unknown software exception";
            }
        }
    }

    /* Calculate length of text buffer */
    TextStringU->MaximumLength = FormatU.Length + SizeOfStrings + 42 * sizeof(WCHAR);

    /* Allocate a buffer for the text */
    TextStringU->Buffer = RtlAllocateHeap(RtlGetProcessHeap(),
                                          HEAP_ZERO_MEMORY,
                                          TextStringU->MaximumLength);

    /* Wrap in SEH to protect from invalid string parameters */
    _SEH2_TRY
    {
        /* Print the string into the buffer */
        StringCbPrintfW(TextStringU->Buffer,
                        TextStringU->MaximumLength,
                        FormatString,
                        Parameters[0],
                        Parameters[1],
                        Parameters[2],
                        Parameters[3]);
        Status = STATUS_SUCCESS;
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        /* Set error and free buffers */
        Status = _SEH2_GetExceptionCode();
        RtlFreeHeap(RtlGetProcessHeap(), 0, TextStringU->Buffer);
        RtlFreeHeap(RtlGetProcessHeap(), 0, CaptionStringU->Buffer);
    }
    _SEH2_END

    if (NT_SUCCESS(Status))
    {
        TextStringU->Length = wcslen(TextStringU->Buffer) * sizeof(WCHAR);
    }

    if (FormatA.Buffer) RtlFreeUnicodeString(&FormatU);

    return Status;
}