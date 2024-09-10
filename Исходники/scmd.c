static void doneh(void)
   {

    clear_sys();

    LONGJMP(SC_gs.cpu, ERR_FREE);}