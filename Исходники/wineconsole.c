void WINECON_Fatal(const char* msg)
{
    WINE_ERR("%s\n", msg);
    ExitProcess(0);
}