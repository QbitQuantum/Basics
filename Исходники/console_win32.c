// returns 0 iff read not complete, >0 bytes read, <0 on error
int
console_read(console_t console, char *buf, int buflen) {
    int i, err;
    DWORD dw=0;
    int lastError;
    int n = 0;

    do {
	// finish the previous overlapped read
	assertb( console->read_pending );
	if( console->read_result ) {
	    dw = console->read_result;
	}
	else {
	    i = GetOverlappedResult(console->read_handle, &console->read_overlap, 
				    &dw, FALSE);
	    if( !i && GetLastError() == ERROR_IO_INCOMPLETE ) {
		n = 0;
		err = 0;
		break;
	    }
	    assertb_syserr(i);
	    console->read_pending = 0;
	}

	n = 0;
	while(1) {
	    i = MIN((int)dw, buflen - n);
	    memcpy(buf + n, console->read_buf, i);
	    if( i < dw ) {
		i = dw - i;
		console->read_result = 5;
		memcpy(console->read_buf, console->read_buf + i, i);
		SetEvent(console->read_event);
		break;
	    }

	    // start a new overlapped read
	    memset(&console->read_overlap, 0, sizeof(console->read_overlap));
	    ResetEvent(console->read_event);
	    console->read_overlap.hEvent = console->read_event;
	    console->read_result = 0;

	    dw = sizeof(console->read_buf);
	    debug(DEBUG_INFO,
		  ("console_read reading dw=%ld\n", dw));
	    i = ReadFile(console->read_handle, console->read_buf, sizeof(console->read_buf), 
			 &dw, &console->read_overlap);
	    lastError = GetLastError();

	    debug(DEBUG_INFO,
		  ("console_read"
		   " i=%d"
		   " dw=%ld"
		   " GetLastError()=%d"
		   " ERROR_IO_PENDING=%d"
		   " IsSet(read_event)=%d"
		   "\n"
		   , i, (long)dw, lastError, ERROR_IO_PENDING
		   , (int)(WaitForSingleObject(console->read_overlap.hEvent, 0) == WAIT_OBJECT_0)
		   ));
	    if( i ) {
		continue;
	    }
	    else if( lastError == ERROR_IO_PENDING ) {
		console->read_pending = 1;
		console->read_result = 0;
		break;
	    }
	    else {
		assertb_syserr(0);
	    }
	}
	
	err = 0;
    } while(0);

    return err ? err : n;
}