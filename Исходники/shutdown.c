/**********************************************************************
 *      AbortSystemShutdownA
 *
 * @unimplemented
 */
BOOL WINAPI
AbortSystemShutdownA(LPCSTR lpMachineName)
{
    ANSI_STRING MachineNameA;
    UNICODE_STRING MachineNameW;
    NTSTATUS Status;
    BOOL rv;

    RtlInitAnsiString(&MachineNameA, (LPSTR)lpMachineName);
    Status = RtlAnsiStringToUnicodeString(&MachineNameW, &MachineNameA, TRUE);
    if (STATUS_SUCCESS != Status)
    {
            SetLastError(RtlNtStatusToDosError(Status));
            return FALSE;
    }

    rv = AbortSystemShutdownW(MachineNameW.Buffer);
    RtlFreeUnicodeString(&MachineNameW);
    SetLastError(ERROR_SUCCESS);
    return rv;
}