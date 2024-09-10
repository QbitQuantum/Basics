static DWORD
proc_stdin_thread(sub_process *pproc)
{
	DWORD in_done;
	for (;;) {
		if (WriteFile( (HANDLE) pproc->sv_stdin[0], pproc->inp, pproc->incnt,
					 &in_done, NULL) == FALSE)
			_endthreadex(0);
		// This if should never be true for anonymous pipes, but gives
		// us a chance to change I/O mechanisms later
		if (in_done < pproc->incnt) {
			pproc->incnt -= in_done;
			pproc->inp += in_done;
		} else {
			_endthreadex(0);
		}
	}
	return 0; // for compiler warnings only.. not reached
}