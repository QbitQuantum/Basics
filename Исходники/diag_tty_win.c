// diag_tty_break #1 : use Set / ClearCommBreak
// and return as soon as break is cleared.
// ret 0 if ok
int diag_tty_break(struct diag_l0_device *dl0d, const unsigned int ms) {
    LARGE_INTEGER qpc1, qpc2;	//for timing verification
    static long correction=0;	//running average offset (us) to add to the timeout
    long real_t;	//"real" duration measured in us
    struct tty_int *wti = (struct tty_int *)dl0d->tty_int;
    int errval=0;

    if (wti->fd == INVALID_HANDLE_VALUE) {
        fprintf(stderr, FLFMT "Error. Is the port open ?\n", FL);
        return diag_iseterr(DIAG_ERR_GENERAL);
    }

    if ( (ms + correction/1000)<1)
        return diag_iseterr(DIAG_ERR_GENERAL);

    QueryPerformanceCounter(&qpc1);
    errval=!SetCommBreak(wti->fd);
    diag_os_millisleep(ms + correction/1000);
    QueryPerformanceCounter(&qpc2);
    errval += !ClearCommBreak(wti->fd);

    if (errval) {
        //if either of the calls failed
        fprintf(stderr, FLFMT "tty_break could not set/clear break!\n", FL);
        return diag_iseterr(DIAG_ERR_GENERAL);
    }
    real_t=(long) (pf_conv * (qpc2.QuadPart-qpc1.QuadPart));

    //now verify if it's within 1ms of the requested delay.
    real_t = real_t - (ms*1000);
    if (real_t < -3000) {
        diag_os_millisleep((unsigned int)(real_t / -1000));
    } else if ((real_t > -1000) && (real_t < 1000)) {
        //good enough:
        return 0;
    }
    //we're here if we were off by more than -3ms or +1ms.
    //correct by a fraction of the error.
    //diag_os_millisleep also does some self-correcting; we don't want to overdo it.
    correction = correction - (real_t / 3);
    //fprintf(stderr, FLFMT "tty_break off by %ldus, new correction=%ldus.\n",
    //	FL, real_t, correction);

    return 0;
}