/*ARGSUSED*/
int main (int     __UNUSED_PARAM(flags),
          char ** __UNUSED_PARAM(cmdline),
          char ** __UNUSED_PARAM(inst))
{
    return (int) WinMain (__mingw_winmain_hInstance, NULL,
                          __mingw_winmain_lpCmdLine, __mingw_winmain_nShowCmd);
}