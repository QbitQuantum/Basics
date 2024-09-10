t_stat sim_load (FILE *fileref, CONST char *cptr, CONST char *fnam, int flag)
{
t_stat r;
int32 i;
uint32 origin, limit;
extern int32 ssc_cnf;
#define SSCCNF_BLO      0x80000000

if (flag)                                               /* dump? */
    return sim_messagef (SCPE_NOFNC, "Command Not Implemented\n");
if (sim_switches & SWMASK ('R')) {                      /* ROM? */
    origin = ROMBASE;
    limit = ROMBASE + ROMSIZE;
    }
else if (sim_switches & SWMASK ('N')) {                 /* NVR? */
    origin = NVRBASE;
    limit = NVRBASE + NVRSIZE;
    ssc_cnf = ssc_cnf & ~SSCCNF_BLO;
    }
else {
    origin = 0;                                         /* memory */
    limit = (uint32) cpu_unit.capac;
    if (sim_switches & SWMASK ('O')) {                  /* origin? */
        origin = (int32) get_uint (cptr, 16, 0xFFFFFFFF, &r);
        if (r != SCPE_OK)
            return SCPE_ARG;
        }
    }
while ((i = Fgetc (fileref)) != EOF) {                   /* read byte stream */
    if (origin >= limit)                                /* NXM? */
        return SCPE_NXM;
    if (sim_switches & SWMASK ('R'))                    /* ROM? */
        rom_wr_B (origin, i);                           /* not writeable */
    else WriteB (origin, i);                            /* store byte */
    origin = origin + 1;
    }
return SCPE_OK;
}