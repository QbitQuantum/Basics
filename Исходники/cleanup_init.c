void    cleanup_sig(int sig)
{

    /*
     * msg_fatal() is safe against calling itself recursively, but signals
     * need extra safety.
     * 
     * XXX While running as a signal handler, can't ask the memory manager to
     * release VSTRING storage.
     */
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN) {
	if (cleanup_trace_path) {
	    (void) REMOVE(vstring_str(cleanup_trace_path));
	    cleanup_trace_path = 0;
	}
	if (cleanup_path) {
	    (void) REMOVE(cleanup_path);
	    cleanup_path = 0;
	}
	if (sig)
	    _exit(sig);
    }
}