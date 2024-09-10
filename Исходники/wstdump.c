void ClearDumpInfo (void)
{
    NTSTATUS   Status;


    //
    // Pause profiling?
    //
    if (fPause) {
	Status = NtPulseEvent (hPauseEvent, NULL);
        if (!NT_SUCCESS(Status)) {
            fprintf (pfLog, "WSTDUMP: ClearDumpInfo () - NtPulseEvent() "
			    "failed for PAUSE event - %lx\n", Status);
            exit (1);
        }
    }
    //
    // Dump data?
    //
    else if (fDump) {
        Status = NtPulseEvent (hDumpEvent, NULL);
        if (!NT_SUCCESS(Status)) {
            fprintf (pfLog, "WSTDUMP: ClearDumpInfo () - NtPulseEvent() "
                            "failed for DUMP event - %lx\n", Status);
            exit (1);
        }
    }
    //
    // Clear data?
    //
    else if (fClear) {
        Status = NtPulseEvent (hClearEvent, NULL);
        if (!NT_SUCCESS(Status)) {
            fprintf (pfLog, "WSTDUMP: ClearDumpInfo () - NtPulseEvent() "
                            "failed for CLEAR event - %lx\n", Status);
            exit (1);
        }
    }
    //
	// Wait for the DONE event..
    //
	Sleep (500);
	Status = NtWaitForSingleObject (hDoneEvent, FALSE, NULL);
    if (!NT_SUCCESS(Status)) {
        fprintf (pfLog, "WSTDUMP: ClearDumpInfo () - NtWaitForSingleObject() "
                        "failed for DONE event - %lx\n", Status);
        exit (1);
    }

} /* ClearDumpInfo() */