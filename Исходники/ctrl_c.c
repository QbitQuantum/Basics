int
main(int argc, char *argv[])
{
    BOOL bRet;
    bRet = GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);  Sleep(1000);  LINE_BARRIER
    return bRet ? 0 : 125;
}