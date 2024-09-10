void loop(void)
{
    char s[2048];
    char file[256];
    int num;

    for (;;)
    {
        if (!fgets(s, 2048, stdin))
        {
            Sleep( 100 );
            continue;
        }
        if (SCAN("uci"))
        {
            printf("id name Irina %s\n", VERSION);
            printf("id author Lucas Monge\n");
            printf("option name Hash type spin min 2 max 1024 default 32");
            printf("option name Personality type combo default Irina var Irina var Steven var Monkey var Donkey var Bull var Wolf var Lion var Rat var Snake var Material var Random var Capture var Advance\n");
            printf("option name Min Time type spin default 0 min 0 max 99\n");
            printf("option name Max Time type spin default 0 min 0 max 99\n");
            printf("uciok\n");
        }
        else if (SCAN("isready"))
        {
            printf("readyok\n");
        }
        else if (SCAN("stop"))
        {
            continue;
        }
        else if (SCAN("quit"))
        {
            break;
        }
        else if (SCAN("fen"))
        {
            board_fen(s);
            printf("%s\n", s);
        }
        else if (SCAN("test"))
        {
            test();
        }
        else if (SCAN("perft file "))
        {
            strcpy(file, s+11);
            strip(file);
            perft_file( file );
        }
        else if (SCAN("perft"))
        {
            num = scan_int(s,"perft");
            perft( num );
        }
        else if (SCAN("ucinewgame"))
        {
            continue;
        }
        else if (SCAN("position"))
        {
            set_position(s);
        }
        else if (SCAN("go"))
        {
            go(s);
        }
        else if (SCAN("setoption name"))
        {
            set_option(s);

        }
    }
}