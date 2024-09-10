VOID WINAPI
EngGetCurrentCodePage( OUT PUSHORT OemCodePage,
                       OUT PUSHORT AnsiCodePage)
{
    *OemCodePage  = GetOEMCP();
    *AnsiCodePage = GetACP();
}