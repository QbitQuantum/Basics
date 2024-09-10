void PrintUserFault(LONG code, const UBYTE *banner)
{
    struct Process *p = (struct Process *)SysBase->ThisTask;
    BPTR Stderr = p->pr_CES ? p->pr_CES : p->pr_COS;

    if (banner != NULL) {
        FPuts(Stderr, (STRPTR)banner);
        FPuts(Stderr, ": ");
    }
    FPuts(Stderr, (STRPTR)ug_StrError(code));
    FPuts(Stderr, "\n");
    Flush(Stderr);
}