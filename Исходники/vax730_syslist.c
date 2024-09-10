t_stat sim_load (FILE *fileref, CONST char *cptr, CONST char *fnam, int flag)
{
t_stat r;
int32 val;
uint32 origin, limit;

if (flag)                                               /* dump? */
    return sim_messagef (SCPE_NOFNC, "Command Not Implemented\n");
origin = 0;                                             /* memory */
limit = (uint32) cpu_unit.capac;
if (sim_switches & SWMASK ('O')) {                      /* origin? */
    origin = (int32) get_uint (cptr, 16, 0xFFFFFFFF, &r);
    if (r != SCPE_OK)
        return SCPE_ARG;
    }

while ((val = Fgetc (fileref)) != EOF) {                 /* read byte stream */
    if (sim_switches & SWMASK ('R')) {                  /* ROM0? */
        return SCPE_NXM;
        }
    else if (sim_switches & SWMASK ('S')) {             /* ROM1? */
        return SCPE_NXM;
        }
    else {
        if (origin >= limit)                            /* NXM? */
            return SCPE_NXM;
        WriteB (origin, val);                           /* memory */
        }
    origin = origin + 1;
    }
return SCPE_OK;
}