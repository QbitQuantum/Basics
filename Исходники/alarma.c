void tranquilizar() {
#ifdef __WIN32__
    timeKillEvent(wintimer);
#else
    alarm(0);
#endif
}