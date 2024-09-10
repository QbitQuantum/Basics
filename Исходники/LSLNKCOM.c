/*====================================================================*/
int freeCommarea(DFHEIBLK *inDfheiptr,
                TraceParms* inTraceParms,
                CICSProgramDesc* pProgramDesc,
                Message* pRequestMessage,
                Message* pResponseMessage) {

    int rc = OK_CODE;

    dfheiptr = inDfheiptr;
    g_pTraceParms = inTraceParms;
    initLog(dfheiptr, inTraceParms);

    if (g_pTraceParms->traceMode == TRUE_CODE) {
       traceMessage(MODULE_NAME, "Entered freeCommarea");
    }

    rc = freeMessage(pRequestMessage);
    rc = freeMessage(pResponseMessage);

    if (g_pTraceParms->traceMode == TRUE_CODE) {
       traceMessage(MODULE_NAME, "Return from freeCommarea");
    }
    return rc;
}