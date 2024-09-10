DWORD WINAPI
eventLogMonitorThreadProc(LPVOID elm_info_param)
{
    EVENTLOGRECORD *pevlr; 
    BYTE bBuffer[BUFFER_SIZE] = { 0 }; 
    DWORD dwRead, dwNeeded, res;
    DWORD reported_next_record, num_records;
    BOOL skip_first = FALSE;
    HANDLE log = NULL, event = NULL;
    WCHAR msgbuf[BUFFER_SIZE];

    eventlogmon_info *elm_info = (eventlogmon_info *) elm_info_param;
  
    control = 0;

    log = OpenEventLog(NULL, L_COMPANY_NAME);
    if (log == NULL) {
        (*elm_info->cb_err)(ELM_ERR_FATAL, 
                            L"Could not open the " L_COMPANY_NAME L" event log."); 
        goto exit_elm_thread_error;
    }
    
    event = CreateEvent(NULL, FALSE, FALSE, NULL);
    NotifyChangeEventLog(log, event);   
    
    pevlr = (EVENTLOGRECORD *) &bBuffer; 

    if (!GetNumberOfEventLogRecords(log, &num_records) ||
        !GetOldestEventLogRecord(log, &reported_next_record)) {
        _snwprintf(msgbuf, BUFFER_SIZE_ELEMENTS(msgbuf),
                   L"error %d getting eventlog info", GetLastError());
        (*elm_info->cb_err)(ELM_ERR_FATAL, msgbuf);
        goto exit_elm_thread_error;
    }

    /* FIXME: we don't handle the situation when the eventlog was cleared,
     *  but our pointer is less than the number of new records. for this
     *  we'll probably have to store a timestamp, and compare against the
     *  event record at next_record. */
    if (((int)elm_info->next_record) < 0) {
        elm_info->next_record = reported_next_record;
    } 
    else if (elm_info->next_record > (reported_next_record + num_records + 1)) {
        /* looks like the eventlog was cleared since we last checked
         *  it. issue a warning and reset */
        elm_info->next_record = reported_next_record;
        (*elm_info->cb_err)(ELM_ERR_CLEARED, L"Eventlog was cleared!\n");
    }
    else {
        /* we need to ensure we SEEK to a valid record; but since
         * it's already been reported, don't report it again. */
        elm_info->next_record--;
        skip_first = TRUE;
    }

    /* first seek to the last record 
     * EVENTLOG_FORWARDS_READ indicates we will get messages in
     *  chronological order.
     * FIXME: test to make sure that this works properly on
     *  overwrite-wrapped logs */
    if (!ReadEventLog(log,                
                      EVENTLOG_FORWARDS_READ | EVENTLOG_SEEK_READ,
                      elm_info->next_record,
                      pevlr,
                      BUFFER_SIZE,
                      &dwRead,
                      &dwNeeded)) {
        dwRead = 0;
        dwNeeded = 0;
    }

    for(;;) {        
        do {
            /* case 5813: if pevlr->Length is 0, we'll have an infinite
             * loop. this could possibly happen if drive is full?
             * just abort if we detect it. */
            while (dwRead > 0 && pevlr->Length > 0) {
                
                if (format_messages && !skip_first) {

                    res = get_formatted_message(pevlr, msgbuf, BUFFER_SIZE);
                    if (res != ERROR_SUCCESS) {
                        _snwprintf(msgbuf, BUFFER_SIZE_ELEMENTS(msgbuf),
                                   L"FormatMessage error %d\n", res);
                        (*elm_info->cb_err)(ELM_ERR_WARN, msgbuf);
                    }
                    else {
                        /* invoke the callback */
                        (*elm_info->cb_format)(pevlr->RecordNumber, 
                                               pevlr->EventType, 
                                               msgbuf, pevlr->TimeGenerated);
                    }
                } else if(!skip_first) {
                    /* xref case 3065: insurance */
                    if (pevlr->RecordNumber != 0 ||
                        pevlr->TimeGenerated != 0) {
                        /* raw callback */
                        (*elm_info->cb_raw)(pevlr);
                    }
                } else {
                    skip_first = FALSE;
                }

                dwRead -= pevlr->Length; 
                pevlr = (EVENTLOGRECORD *) ((LPBYTE) pevlr + pevlr->Length); 
            }
            
            pevlr = (EVENTLOGRECORD *) &bBuffer; 
        } while (ReadEventLog(log,                
                              EVENTLOG_FORWARDS_READ |  
                              EVENTLOG_SEQUENTIAL_READ, 
                              0,            
                              pevlr,        
                              BUFFER_SIZE,  
                              &dwRead,      
                              &dwNeeded));
        
        if((res = GetLastError()) != ERROR_HANDLE_EOF) {
            //FIXME: assert GetLastError() is appropriate
            _snwprintf(msgbuf, BUFFER_SIZE_ELEMENTS(msgbuf),
                       L"Unexpected error %d reading event log\n", res);
            (*elm_info->cb_err)(ELM_ERR_WARN, msgbuf);
        }

        if (do_once)
            break;

        /* the event is auto-reset.
           timeout because NotifyChangeEventLog is not reliable. */
        WaitForSingleObject(event, MINIPULSE);

        if(control)
            break;
    }
    
exit_elm_thread_error:

    if (log != NULL)
        CloseEventLog(log); 

    if (event != NULL)
        CloseHandle(event);

    free(elm_info);

    /* FIXME: need ExitThread()? */
    return 0;
}