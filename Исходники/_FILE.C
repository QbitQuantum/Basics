void __cdecl __endstdio(void) {
    /* flush all streams */
    _flushall();

    /* if in callable exit, close all streams */
    if (_exitflag) {
        _fcloseall();
    }

    _free_crt(__piob);
}