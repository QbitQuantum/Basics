NORETURN void _SC_timeout_cont(int sig)
   {JMP_BUF *cpu;

/* io_printf(stdout, "Timeout %d\n", sig); */
    SC_timeout(0, _SC_timeout_cont, NULL, 0);
    
    cpu = _SC_get_to_buf(-1);

    LONGJMP(*cpu, 1);}