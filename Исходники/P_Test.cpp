// *************************************************************
//   Configuration helpers
// *************************************************************
int
run (int argc, ACE_TCHAR *argv[])
{
    int rc = 0;

    ProactorTask task1(cfg);

    RecvFactory r_factory;
    SendFactory s_factory;

    PSessionManager r_manager (task1, r_factory,"R_Manager");
    PSessionManager s_manager (task1, s_factory,"S_Manager");

    Acceptor  acceptor  (r_manager);
    Connector connector (s_manager);

    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    if (task1.start () == 0)
    {
        task1.enable_event_loop();

        ACE_Time_Value timeout (cfg.timeout(), 0);
        r_manager.set_timeout (timeout);
        s_manager.set_timeout (timeout);

        if (cfg.both() != 0 || cfg.connections () == 0) // Acceptor
        {
            if (acceptor.start (ACE_INET_Addr (cfg.listen_port())) == 0)
                rc = 1;
        }

        if (cfg.both() != 0 || cfg.connections () > 0) // Connector
        {
            ACE_INET_Addr addr;

            addr.set (cfg.connect_port(), cfg.connect_host());

            rc += connector.start (addr, cfg.connections ());
        }
    }

    time_begin = ACE_OS::gettimeofday ();

    if (rc > 0)
    {
        //task1.enable_event_loop();
        
        ACE_Time_Value  sleep_time (cfg.seconds());
        
        while ( sleep_time != ACE_Time_Value::zero)
        {
            ACE_Countdown_Time countdown ( & sleep_time );
            ACE_OS::sleep (sleep_time );
        }

        if (cfg.seconds () == 0)
        {
            bool flgExit = false;
            for (;!flgExit;)
            {
                char c;
                cout << "\nPress Q to stop=>" << flush;
                cin.clear ();
                cin >> c;
                switch (toupper (c))
                {
                case 'Q':
                    flgExit = true;
                    break;
                case 'P':
                    cout << "\n*** Connector: PendingConnects="
                        << connector.get_ref_cnt()
                        << " Senders="
                        << s_manager.get_number_connections ()
                        << "\n*** Acceptor: PendingAccepts="
                        << acceptor.get_ref_cnt()
                        << " Receivers="
                        << r_manager.get_number_connections ();
                break;
                }//switch
            }//for
        }//if cfg.seconds