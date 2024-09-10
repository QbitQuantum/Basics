int pc_mp_send_switches_0(void)
{
    char  *msg, *str;
    TERM  msw;
    int   msglen, msgsiz;
    int   vals[2];
    int   i, n;

    msglen = 0;
    msgsiz = 65536;
    msg = MALLOC(msgsiz);

    for (i = 0; i < occ_switch_tab_size; i++) {
        msw = bpx_get_arg(1, prism_sw_ins_term(occ_switches[i]->id));
        str = (char *)bpx_term_2_string(msw);

        n = strlen(str) + 1;

        if (msgsiz <= msglen + n) {
            msgsiz = (msglen + n + 65536) & ~65535;
            msg = REALLOC(msg, msgsiz);
        }

        strcpy(msg + msglen, str);
        msglen += n;
    }

    msg[msglen++] = '\0'; /* this is safe */

    vals[0] = msglen;
    vals[1] = occ_switch_tab_size;

    MPI_Gather(vals, 2, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Send(msg, msglen, MPI_CHAR, 0, TAG_SWITCH_REQ, MPI_COMM_WORLD);

    free(msg);

    return BP_TRUE;
}