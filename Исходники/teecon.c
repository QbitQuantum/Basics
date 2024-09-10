int main(int argc, char *argv[])
{
    int rc = -1;
    int index_cmd;

    index_cmd = mygetopt(argc, argv);
    if (optH) {
        usage();
        return 0;
    }
    if (index_cmd >= argc || !logname) {
        fprintf(stderr, "Type 'TEECON -?' to help.\n");
        return 1;
    }

    if (optA) {
        rc = _dos_open(logname, O_RDWR, &tee_handle);
        if (rc == 0) my_doslseek(tee_handle, 0L, 2);
        else if (rc == 2) optO = 1; /* retry with creat when the file is not found */
        else optO = 0;
    }
    if (optO && tee_handle == -1) rc = _dos_creat(logname, _A_NORMAL, &tee_handle);

    if (rc != 0) {
        fprintf(stderr, "FATAL: can't open the log file '%s'\n", logname);
        return -1;
    }

    my_psp = my_getpsp();
    org_int21 = _dos_getvect(0x21);
    _dos_setvect(0x21, Int21Handler);
    if (argv[index_cmd]) {
        rc = spawnvp(P_WAIT, argv[index_cmd], (char const * const *)(argv + index_cmd));
    }
    _dos_setvect(0x21, org_int21);
    fprintf(stderr, "%s : result=%d\n", argv[index_cmd], rc);
    if (tee_handle != -1) _dos_close(tee_handle);

    return rc;
}