VOID
TermDiamond(
    VOID
    )
{
    if(FdiContext) {
        FDIDestroy(FdiContext);
        FdiContext = NULL;
    }
}