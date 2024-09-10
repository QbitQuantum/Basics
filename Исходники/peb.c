NTSYSAPI
NTSTATUS
STDAPIVCALLTYPE
RtlSetThreadIsCritical(
    IN  BOOLEAN  NewValue,
    OUT PBOOLEAN OldValue OPTIONAL,
    IN  BOOLEAN  CheckFlag
    )
{
    PPEB     Peb;
    ULONG    Enable;
    NTSTATUS Status;

    if ( ARGUMENT_PRESENT(OldValue) ) {
        *OldValue = FALSE;
    }

    Peb = RtlGetCurrentPeb();
    if ( CheckFlag
         && ! (Peb->NtGlobalFlag & FLG_ENABLE_SYSTEM_CRIT_BREAKS) ) {
        return STATUS_UNSUCCESSFUL;
    }
    if ( ARGUMENT_PRESENT(OldValue) ) {
        NtQueryInformationThread(NtCurrentThread(),
                                 ThreadBreakOnTermination,
                                 &Enable,
                                 sizeof(Enable),
                                 NULL);

        *OldValue = (BOOLEAN) Enable;
    }

    Enable = NewValue;

    Status = NtSetInformationThread(NtCurrentThread(),
                                    ThreadBreakOnTermination,
                                    &Enable,
                                    sizeof(Enable));

    return Status;
}