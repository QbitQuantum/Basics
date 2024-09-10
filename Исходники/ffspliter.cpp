int main(int argc, char *argv[])
{
    char   *input, *output;
    int64_t start,  end;

#if 1
    if (argc < 5) {
        printf(
            "ffspliter: tools for spliter media file\n"
            "usage: ffspliter input start end output\n"
            "input support any file format a        \n"
            "output support only flv and mp4 format \n"
            "start and end time is in ms unit       \n"
        );
        return -1;
    }

    input  = argv[1];
    output = argv[4];
    start  = _atoi64(argv[2]);
    end    = _atoi64(argv[3]);
#else
    input  = "rtmp://live.hkstv.hk.lxdns.com/live/hks";
    output = "c:\\record.mp4";
    start  = -1;
    end    = 60000;
#endif

    // set console ctrl handler
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)console_ctrl_handler, TRUE);

    // start split media file
    split_media_file(output, input, start, end, split_progress_callback);

    _getch();
    return 0;
}