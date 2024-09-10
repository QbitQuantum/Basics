/*
 * Send serial special codes.
 */
static void serial_special(void *handle, Telnet_Special code)
{
    Serial serial = (Serial) handle;

    if (serial->port && code == TS_BRK) {
	logevent(serial->frontend, "Starting serial break at user request");
	SetCommBreak(serial->port);
	/*
	 * To send a serial break on Windows, we call SetCommBreak
	 * to begin the break, then wait a bit, and then call
	 * ClearCommBreak to finish it. Hence, I must use timing.c
	 * to arrange a callback when it's time to do the latter.
	 * 
	 * SUS says that a default break length must be between 1/4
	 * and 1/2 second. FreeBSD apparently goes with 2/5 second,
	 * and so will I. 
	 */
	serial->clearbreak_time =
	    schedule_timer(TICKSPERSEC * 2 / 5, serbreak_timer, serial);
	serial->break_in_progress = TRUE;
    }

    return;
}