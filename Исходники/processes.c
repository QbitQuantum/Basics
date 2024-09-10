NTSTATUS NTAPI
PsaCaptureProcessesAndThreads(OUT PSYSTEM_PROCESS_INFORMATION *ProcessesAndThreads)
{
  PSYSTEM_PROCESS_INFORMATION pInfoBuffer = NULL;
  SIZE_T nSize = 0x8000;
  NTSTATUS Status;

  if(ProcessesAndThreads == NULL)
  {
    return STATUS_INVALID_PARAMETER_1;
  }

  /* FIXME: if the system has loaded several processes and threads, the buffer
            could get really big. But if there's several processes and threads, the
            system is already under stress, and a huge buffer could only make things
            worse. The function should be profiled to see what's the average minimum
            buffer size, to succeed on the first shot */
  do
  {
    PVOID pTmp;

    /* free the buffer, and reallocate it to the new size. RATIONALE: since we
       ignore the buffer's contents at this point, there's no point in a realloc()
       that could end up copying a large chunk of data we'd discard anyway */
    PsaiFree(pInfoBuffer);
    pTmp = PsaiMalloc(nSize);

    if(pTmp == NULL)
    {
      DPRINT(FAILED_WITH_STATUS, "PsaiMalloc", STATUS_NO_MEMORY);
      Status = STATUS_NO_MEMORY;
      break;
    }

    pInfoBuffer = pTmp;

    /* query the information */
    Status = NtQuerySystemInformation(SystemProcessInformation,
                                      pInfoBuffer,
                                      nSize,
                                      NULL);

    /* double the buffer size */
    nSize *= 2;
  } while(Status == STATUS_INFO_LENGTH_MISMATCH);

  if(!NT_SUCCESS(Status))
  {
    DPRINT(FAILED_WITH_STATUS, "NtQuerySystemInformation", Status);
    return Status;
  }

  *ProcessesAndThreads = pInfoBuffer;
  return STATUS_SUCCESS;
}