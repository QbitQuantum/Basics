static VOID
ssh_event_log_cb(SshLogFacility facility,
                 SshLogSeverity severity,
                 const char *msg,
                 PDRIVER_OBJECT driver)
{
  PIO_ERROR_LOG_PACKET pkt;
  UNICODE_STRING uc;
  ANSI_STRING ansi;
  size_t pkt_size;

  if (msg == NULL)
    return;

  if ((SSH_GET_IRQL() > SSH_PASSIVE_LEVEL) && (the_interceptor != NULL))
    {
      /* Event logging can't be performed at a raised IRQL, so we have to
         schedule a work item to complete the operation */
      SshEventLogRequest request = ssh_calloc(1, sizeof(*request));

      if (request == NULL)
        return;

      request->msg = ssh_strdup(msg);
      if (request->msg == NULL)
        {
          ssh_free(request);
          return;
        }

      request->facility = facility;
      request->severity = severity;
      request->driver = driver;

      if (ssh_ndis_wrkqueue_queue_item(the_interceptor->work_queue,
                                       ssh_event_log_work_queue_cb,
                                       request) == FALSE)
        {
          ssh_free(request->msg);
          ssh_free(request);
        }
      
      return;
    }

  /* Compose unicode error message string */
  RtlInitAnsiString(&ansi, msg);

  /* Calculate the maximum length a error log entry can contain */
  uc.Length = 0;
  uc.MaximumLength = ansi.MaximumLength * sizeof(WCHAR);
  if ((sizeof(IO_ERROR_LOG_PACKET) + 
       uc.MaximumLength) > ERROR_LOG_MAXIMUM_SIZE)
    {
      char *msg_copy;

      /* The message must be splitted into several fragments */
      uc.MaximumLength = ERROR_LOG_MAXIMUM_SIZE - sizeof(IO_ERROR_LOG_PACKET);
      ansi.MaximumLength = uc.MaximumLength / sizeof(WCHAR);
      ansi.Length = ansi.MaximumLength-1;

      /* Remember to copy the original message before truncating. Otherwice we
         _could_ cause some ugly side effects in the calling code.  */
      msg_copy = ssh_strdup(msg);
      if (msg_copy != NULL)
        {
          /* We write the tail of the message first, so the fractions are
             displayed in sensible order (with the default setup of the 
             Windows' Event Viever) */
          ssh_event_log_cb(facility, severity, 
                           &(msg_copy[ansi.Length]), driver);
          msg_copy[ansi.Length] = 0x00;
          ssh_event_log_cb(facility, severity, msg_copy, driver);
          ssh_free(msg_copy);
        }

      return;
    }

  /* Calc error log packet size */
  pkt_size = sizeof(IO_ERROR_LOG_PACKET) + uc.MaximumLength;
  SSH_ASSERT(pkt_size <= ERROR_LOG_MAXIMUM_SIZE);

  /* Allocate error log entry */
  pkt = IoAllocateErrorLogEntry(driver, (UCHAR)pkt_size);
  if (pkt != NULL)
    {
      switch (severity)
        {
        case SSH_LOG_INFORMATIONAL:
          pkt->ErrorCode = SSH_MSG_INFORMATIONAL;
          break;

        case SSH_LOG_NOTICE:
          pkt->ErrorCode = SSH_MSG_NOTICE;
          break;

        case SSH_LOG_WARNING:
          pkt->ErrorCode = SSH_MSG_WARNING;
          break;

        case SSH_LOG_ERROR:
          pkt->ErrorCode = SSH_MSG_ERROR;
          break;

        case SSH_LOG_CRITICAL:
          pkt->ErrorCode = SSH_MSG_CRITICAL;
          break;

        default:
          SSH_NOTREACHED;
          break;
        }

      /* Init the attributes of error log entry */
      pkt->MajorFunctionCode = 0;
      pkt->RetryCount = 0;
      pkt->DumpDataSize = 0;
      pkt->NumberOfStrings = 1;
      pkt->StringOffset = FIELD_OFFSET(IO_ERROR_LOG_PACKET, DumpData);
      pkt->EventCategory = 0; 
      pkt->UniqueErrorValue = pkt->ErrorCode;
      pkt->FinalStatus = STATUS_SUCCESS;
      pkt->SequenceNumber = 0;
      pkt->IoControlCode = 0;
      /* Perform ANSI -> UNICODE conversion */
      uc.Buffer = (PUSHORT)&(pkt->DumpData[0]);
      if (NT_SUCCESS(RtlAnsiStringToUnicodeString(&uc, &ansi, FALSE)))
        IoWriteErrorLogEntry(pkt);
      else
        IoFreeErrorLogEntry(pkt);
    }
}