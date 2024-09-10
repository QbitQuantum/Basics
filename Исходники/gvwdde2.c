/* This should be during shutdown in WinMain */
void
dde_uninitialise()
{
    dde_enable_server(FALSE);
    DdeFreeStringHandle(idInst, hszService);
    DdeFreeStringHandle(idInst, hszTopic);
    DdeUninitialize(idInst);
    idInst = 0;
}