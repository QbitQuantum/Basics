/** main function
 * \param argc ?
 * \param argv ?
 * \return 0
*/
int
main(int argc, char **argv)
{
     int i;
     char *ol = "csgVS";
     extern char *optarg;
     extern int optind;
     struct sigaction sa;

     argv_global  = xstrdup(argv[0]);
     all_argv = argv;
     sprintf(conf.confpath, "%s/"DEF_CONF, getenv("HOME"));

     while((i = getopt(argc, argv, "hviSc:s:g:C:V:")) != -1)
     {

          /* For options who need WMFS running */
          if(strchr(ol, i) && !(dpy = XOpenDisplay(NULL)))
               errx(EXIT_FAILURE, "cannot open X server.");

          switch(i)
          {
          case 'h':
          default:
               printf("usage: %s [-ihvS] [-C <file>] [-c <uicb function> <cmd> ] [-g <argument>] [-s <screen_num> <string>] [-V <viwmfs cmd]\n"
                      "   -C <file>                 Load a configuration file\n"
                      "   -c <uicb_function> <cmd>  Execute an uicb function to control WMFS\n"
                      "   -g <argument>             Show information about wmfs status\n"
                      "   -s <screen_num> <string>  Set the bar(s) statustext\n"
                      "   -V <viwmfs cmd>           Manage WMFS with vi-like command\n"
                      "   -S                        Update status script\n"
                      "   -h                        Show this page\n"
                      "   -i                        Show informations\n"
                      "   -v                        Show WMFS version\n", argv[0]);
               exit(EXIT_SUCCESS);
               break;

          case 'i':
               printf("WMFS - Window Manager From Scratch By Martin Duquesnoy\n");
               exit(EXIT_SUCCESS);
               break;

          case 'v':
               printf("WMFS "WMFS_VERSION"\n");
               exit(EXIT_SUCCESS);
               break;

          case 'S':
               update_status();
               XCloseDisplay(dpy);
               exit(EXIT_SUCCESS);
               break;

          case 'C':
               strncpy(conf.confpath, optarg, sizeof(conf.confpath));
               break;

          case 'c':
               exec_uicb_function(optarg, argv[optind]);
               XCloseDisplay(dpy);
               exit(EXIT_SUCCESS);
               break;

          case 's':
               if(argc > 3)
                    set_statustext(atoi(optarg), argv[3]);
               else
                    set_statustext(-1, optarg);
               XCloseDisplay(dpy);
               exit(EXIT_SUCCESS);
               break;

          case 'g':
               getinfo(optarg);
               XCloseDisplay(dpy);
               exit(EXIT_SUCCESS);
               break;
          case 'V':
               viwmfs(argc, argv);
               XCloseDisplay(dpy);
               exit(EXIT_SUCCESS);
               break;
          }
     }

     /* Check if WMFS can open X server */
     if(!(dpy = XOpenDisplay(NULL)))
          errx(EXIT_FAILURE, "cannot open X server.");

     /* Set signal handler */
     memset(&sa, 0, sizeof(sa));
     sa.sa_handler = signal_handle;
     sigemptyset(&sa.sa_mask);
     sigaction(SIGQUIT, &sa, NULL);
     sigaction(SIGTERM, &sa, NULL);
     sigaction(SIGCHLD, &sa, NULL);

     /* Check if an other WM is already running; set the error handler */
     XSetErrorHandler(errorhandler);

     /* Let's Go ! */
     init();
     scan();
     mainloop();
     quit();

     return 0;
}