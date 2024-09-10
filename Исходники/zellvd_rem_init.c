int
zellvd_rem_init(struct sis1100_softc* sc, int reset)
{
/* sc->sem_hw must be held by caller!*/
#define MIN_FV_1 1
#define MAX_FV_1 17
#define MIN_FV_2 17
#define MAX_FV_2 17
#define MIN_FV_3 1
#define MAX_FV_3 1
    int min_fv=0, max_fv=0;
    u_int32_t hv, fk, fv;

    hv=(sc->remote_ident>>8)&0xff;
    fk=(sc->remote_ident>>16)&0xff;
    fv=(sc->remote_ident>>24)&0xff;

    switch (sc->remote_ident&0x00ffff00) {
    case 0x00010100: /* LVD controller with F1 */
        min_fv=MIN_FV_1;
        max_fv=MAX_FV_1;
        break;
    case 0x00010200: /* LVD controller with GPX */
        min_fv=MIN_FV_2;
        max_fv=MAX_FV_2;
        break;
    case 0x00010300: /* LVD controller with both F1 and GPX */
        min_fv=MIN_FV_3;
        max_fv=MAX_FV_3;
        break;
    default:
        pERROR(sc, "zellvd: remote hw/fw type not supported");
        return -1;
    }
    if (fv<min_fv) {
        pERROR(sc, "zellvd: remote firmware version too old;"
                " at least version %d is required.",
                min_fv);
        return -1;
    }
    if (fv>max_fv) {
        pINFO(sc, "zellvd: Driver not tested with"
                " remote firmware versions higher than %d.",
                max_fv);
    }

    if (reset>0)
        lvd_writeremreg(sc, cr, 0, 1); /* reset cr */

    return 0;
}