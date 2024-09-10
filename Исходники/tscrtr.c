static void sig_handler(int sig)
   {int err;

    SC_setup_sig_handlers(sig_handler, NULL, 0, FALSE);

    SC_LOCKON(tlock);

    err = SC_retrace_exe(NULL, -1, 60000);

    SC_ASSERT(err == TRUE);

    LONGJMP(cpu, TRUE);

    SC_LOCKOFF(tlock);

    return;}