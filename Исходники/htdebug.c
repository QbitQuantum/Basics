void  DrvDbgPrint(
    char * pch,
    ...)
{
    va_list ap;
    va_start(ap, pch);

    EngDebugPrint("",pch,ap);

    va_end(ap);
}