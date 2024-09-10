void CreateConsole()
{
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
    setvbuf(stdout, NULL, _IONBF, 0);
}