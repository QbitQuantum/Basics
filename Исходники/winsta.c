BOOL APIENTRY
NtUserUnlockWindowStation(HWINSTA hWindowStation)
{
    PWINSTATION_OBJECT Object;
    NTSTATUS Status;
    BOOL Ret;

    TRACE("About to set process window station with handle (%p)\n",
          hWindowStation);

    if (gpidLogon != PsGetCurrentProcessId())
    {
        ERR("Unauthorized process attempted to unlock the window station!\n");
        EngSetLastError(ERROR_ACCESS_DENIED);
        return FALSE;
    }

    Status = IntValidateWindowStationHandle(hWindowStation,
                                            UserMode,
                                            0,
                                            &Object,
                                            0);
    if (!NT_SUCCESS(Status))
    {
        TRACE("Validation of window station handle (%p) failed\n",
              hWindowStation);
        SetLastNtError(Status);
        return FALSE;
    }

    Ret = (Object->Flags & WSS_LOCKED) == WSS_LOCKED;
    Object->Flags &= ~WSS_LOCKED;

    ObDereferenceObject(Object);
    return Ret;
}