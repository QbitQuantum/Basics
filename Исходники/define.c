//=====================================================================
int dcl_define_logical(PARAM_T *p,PARAM_T *q)
{
    char    token[MAX_TOKEN];
    char    value[LOGICAL_MAX_VALUE];
    char    name[LOGICAL_MAX_NAME];
    char    dosfile[_MAX_PATH];
    char    drive[_MAX_DRIVE];
    char    dir[_MAX_DIR];
    char    fname[_MAX_FNAME];
    char    ext[_MAX_EXT];
    int     i       = 0;
    int     log     = 1;
    int     retcod  = DCL_OK;

    *token = 0; *value = 0; *name = 0;

    for (i = 0; q[i].tag; i++) {
        if (q[i].flag & PRESENT) 
            switch (q[i].tag) {
            case 6:                                 /* /LOG     */
                log = TRUE;
                break;
            case 7:                                 /* /NOLOG   */
                log = FALSE;
                break;
            default:
                (void)dcl_printf(dcl[D].SYS_OUTPUT,"Invalid command qualifier\n");
                _SEVERITY = 2;
                _STATUS = 19;
                retcod = DCL_ERROR;
            } /* end switch */
    }   /* end for */

    if (retcod == DCL_OK) {
        dcl_string(p[0].value,name,MAX_TOKEN);
        dcl_string(p[1].value,value,MAX_TOKEN);
        (void)logical_get(name,token);
        retcod = logical_put(name,value,LOG_USER);
        if (log && *token && retcod == 0) {
            (void)dcl_printf(dcl[D].SYS_OUTPUT,"%s superseded\n",name);
        }
        if (strcasecmp(name,"SYS$OUTPUT") == 0) {
            if (dcl[D].SYS_OUTPUT != stdout) {
                //(void)fclose(dcl[D].SYS_OUTPUT);
            }
            if (strcasecmp(value, "tt") == 0) {
                dcl[D].SYS_OUTPUT = stdout;
                strcpy(dcl[D].outname, name);
            }
            else {
            	cvfs_vms_to_dos(name,dosfile,&i);
                _splitpath(dosfile,drive,dir,fname,ext);
                if (strlen(ext) == 0) strcat(dosfile,".lis");
                dcl[D].SYS_OUTPUT = fopen(dosfile,"at");
                if (dcl[D].SYS_OUTPUT == NULL) {
                    dcl[D].SYS_OUTPUT = stdout;
                    strcpy(dcl[D].outname, "SYS$OUTPUT");
                    }
                else {
                    strncpy(dcl[D].outname,dosfile,_MAX_PATH);
                    }
                }
        	}
        }

    return(retcod);
}