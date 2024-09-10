EAPI_MAIN int elm_main(int argc, char** argv)
{
    winmain();

    elm_run();
    elm_shutdown();
    return 0;
}