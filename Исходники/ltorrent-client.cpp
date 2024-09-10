int main(int argc, char* argv[])
{       
        if (argc == 1) {
            printhelp(argv[0]);
        }
        int tmp;
        char torrentfile[255];
        int usrpid = 0;
        int mypid;
        char pidfilename[255];
        char ip[16];
        int delay = 10;
        strcpy(ip, "0.0.0.0");
        strcpy(pidfilename, argv[0]);
        strcat(pidfilename, ".pid");

        while((tmp=getopt(argc,argv,"ht:p:f:b:d:"))!=-1) {
             switch(tmp) {
                case 'h':
                    printhelp(argv[0]);
                    break;
                case 't':
                    strcpy(torrentfile, optarg);
                    break;
                case 'p':
                    usrpid = atoi(optarg);
                    break;
                case 'f':
                    strcpy(pidfilename, optarg);
                    break;
                case 'b':
                    strcpy(ip, optarg);
                    break;
                case 'd':
                    delay = atoi(optarg);
                    break;
                default:
                    printhelp(argv[0]);
                    break;
             }
        }
        if (usrpid == 0) {
            printhelp(argv[0]);
        }
        mypid = ::getpid();
        std::signal(SIGINT, exit_signalHandler);
        std::signal(SIGTERM, exit_signalHandler);

        using namespace libtorrent;

        // set peer_id to nodename
        char hostname[HOST_NAME_MAX];
        gethostname(hostname, HOST_NAME_MAX);
        char buff[21];
        snprintf(buff, sizeof(buff), "%20s", hostname);
        peer_id my_peer_id = sha1_hash(buff);
        s.set_peer_id(my_peer_id);
        error_code ec;

        // set up torrent session
        s.listen_on(std::make_pair(6881, 6889), ec, ip);
        if (ec)
        {
                fprintf(stderr, "failed to open listen socket: %s\n", ec.message().c_str());
                return 1;
        }

        // create torrent object
        add_torrent_params p;
        p.save_path = "./";
        p.ti = new torrent_info(torrentfile, ec);
        if (ec)
        {
                fprintf(stderr, "%s\n", ec.message().c_str());
                return 1;
        }

        // start downloading torrent
        torrent_handle torrent = s.add_torrent(p, ec);
        if (ec)
        {
                fprintf(stderr, "%s\n", ec.message().c_str());
                return 1;
        }

        // create pidfile
        std::ofstream pidfile;
        pidfile.open(pidfilename);
        pidfile << mypid;
        pidfile << "\n";
        pidfile.close();

        std::vector<torrent_status> vts;
        s.get_torrent_status(&vts, &yes, 0);
        torrent_status& st = vts[0];
        boost::int64_t remains = st.total_wanted - st.total_wanted_done;
        fprintf(stdout, "Remains: %i\n", remains);
        //fprintf(stdout, "Torrent: %i\n", torrent);

        while( remains > 0 && run ) {
            usleep(delay*1000000);
            std::vector<torrent_status> vts;
            s.get_torrent_status(&vts, &yes, 0);
            torrent_status& st = vts[0];
            remains = st.total_wanted - st.total_wanted_done;
            fprintf(stdout, "Remains: %i\n", remains);
            torrent.force_reannounce();

        }
        // send SIGUSR1 to process
        fprintf(stdout, "Done with torrent. Sending SIGUSR1 to PID %i\n", usrpid); 
        kill(usrpid, SIGUSR1);
        while (run) {
            usleep(delay*1000000);
            torrent.force_reannounce();
        }
        s.abort();
        remove(pidfilename);
        fprintf(stdout, "Exit.\n"); 
        return 0;
        
}