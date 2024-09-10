/*
 * OutsideEditorWork()
 *
 * This will execute an outside editor for anyone.
 */
void OutsideEditorWork(char *EditLine)
{
    char cmdline[90];
    extern FILE *upfd;
    extern int outPut;

    doCR();	/* this gets crtColumn back to zero */
    sprintf(cmdline, "%stempmsg.sys", cfg.DepData.EditArea);

    if (!redirect(cmdline, INPLACE_OF)) return;

    mFormat(msgBuf.mbtext, oChar, doCR);
    undirect();

    MakeCmdLine(cmdline, EditLine, "", sizeof cmdline - 1);
    if (cfg.DepData.IBM) ModemShutdown(FALSE);
    CitSystem(TRUE, "%s %stempmsg.sys", cmdline, cfg.DepData.EditArea);
    if (cfg.DepData.IBM) {
	ModemOpen(FALSE);
	if (!gotCarrier() && strLen(cfg.DepData.sDisable) == 0)
	    DisableModem(FALSE);
    }
    /* homeSpace(); */    /* Commented out for 120.692 */
    msgBuf.mbtext[0] = 0;

    sprintf(cmdline, "%stempmsg.sys", cfg.DepData.EditArea);
    msgBuf.mbtext[0] = 0;
    ingestFile(cmdline, msgBuf.mbtext);
    unlink(cmdline);
}