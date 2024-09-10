static VOID PhInitializeSystemInformation(
    VOID
    )
{
    NtQuerySystemInformation(
        SystemBasicInformation,
        &PhSystemBasicInformation,
        sizeof(SYSTEM_BASIC_INFORMATION),
        NULL
        );
}