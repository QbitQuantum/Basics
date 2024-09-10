t_stat pt_svc (UNIT *uptr)
{
int32 c;
uint32 cmd;
uint32 st;

switch (pt_cmd) {                                       /* case on state */

    case PTS_INIT:                                      /* I/O init */
        st = chan_get_cmd (pt_dib.dva, &cmd);           /* get command */
        if (CHS_IFERR (st))                             /* channel error? */
            return pt_chan_err (st);
        if ((cmd == PTS_WRITE) ||                       /* valid command? */
            ((cmd & 0x7F) == PTS_READ))
            pt_cmd = cmd;                               /* next state */
        else pt_cmd = PTS_END;                          /* no, end state */
        sim_activate (uptr, chan_ctl_time);             /* continue thread */
        break;

    case PTS_READ:
    case PTS_READI:
        sim_activate (uptr, uptr->wait);                /* continue thread */
        if ((uptr->flags & UNIT_ATT) == 0)              /* not attached? */
            return ptr_stopioe? SCPE_UNATT: SCPE_OK;
        if ((c = getc (uptr->fileref)) == EOF) {        /* read char */
            if (feof (uptr->fileref)) {                 /* end of file? */
                chan_set_chf (pt_dib.dva, CHF_LNTE);    /* length error */
                pt_cmd = PTS_END;                       /* end state */
                break;
                }
            else {                                      /* real error */
                perror ("PTR I/O error");
                clearerr (uptr->fileref);
                chan_set_chf (pt_dib.dva, CHF_XMDE);    /* data error */
                return pt_chan_err (SCPE_IOERR);        /* force uend */
               }
            }
        uptr->pos = uptr->pos + 1;
        if (c != 0)                                     /* leader done? */
            ptr_nzc = 1;                                /* set flag */
        if ((pt_cmd == PTS_READI) || ptr_nzc) {
            st = chan_WrMemB (pt_dib.dva, c);           /* write to memory */
            if (CHS_IFERR (st))                         /* channel error? */
                return pt_chan_err (st);
            if (st == CHS_ZBC)                          /* bc == 0? */
                pt_cmd = PTS_END;                       /* end state */
            }
        break;

    case PTS_WRITE:                                     /* write */
        sim_activate (uptr, pt_unit[PTP].wait);         /* continue thread */
        if ((pt_unit[PTP].flags & UNIT_ATT) == 0)       /* not attached? */
            return ptp_stopioe? SCPE_UNATT: SCPE_OK;
        st = chan_RdMemB (pt_dib.dva, &c);              /* read from channel */
        if (CHS_IFERR (st))                             /* channel error? */
            return pt_chan_err (st);
        if (putc (c, pt_unit[PTP].fileref) == EOF) {
            perror ("PTP I/O error");
            clearerr (pt_unit[PTP].fileref);
            chan_set_chf (pt_dib.dva, CHF_XMDE);        /* data error */
            return pt_chan_err (SCPE_IOERR);            /* force uend */
            }
        pt_unit[PTP].pos = pt_unit[PTP].pos + 1;
        if (st == CHS_ZBC)                              /* bc == 0? */
            pt_cmd = PTS_END;                           /* end state */
        break;

    case PTS_END:                                       /* command done */
        st = chan_end (pt_dib.dva);                     /* set channel end */
        if (CHS_IFERR (st))                             /* channel error? */
            return pt_chan_err (st);
        if (st == CHS_CCH) {                            /* command chain? */
            pt_cmd = PTS_INIT;                          /* restart thread */
            sim_activate (uptr, chan_ctl_time);
            }
        break;
        }

return SCPE_OK;
}