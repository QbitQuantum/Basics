    /** \fn content(po::variables_map const& vm)
        \brief Execute the NEST synapse Miniapp.
        \param vm encapsulate the command line and all needed informations
     */
    void model_content(po::variables_map const& vm)
    {
        PoorMansAllocator poormansallocpool;
        double dt = vm["dt"].as<double>();
        int iterations = vm["iterations"].as<int>();
        const int num_connections = vm["nConnections"].as<int>();
        const int num_detectors = vm["nDetectors"].as<int>();
        bool with_connector = vm.count("connector") > 0;
        bool with_manager = vm.count("manager") > 0;

        //will turn into ptr to base class if more synapse are implemented
        tsodyks2* syn;
        ConnectorBase* conn = NULL;

        //preallocate vector for results
        std::vector<spikedetector> detectors(num_detectors);
        std::vector<targetindex> detectors_targetindex(num_detectors);

        // register spike detectors

        connectionmanager* cn = NULL;

        for(unsigned int i=0; i < num_detectors; ++i) {
            detectors[i].set_lid(i);    //give nodes a local id
            //scheduler stores pointers to the spike detectors
            detectors_targetindex[i] = scheduler::add_node(&detectors[i]);  //add them to the scheduler
        }

        if (vm["model"].as<std::string>() == "tsodyks2") {
            const double delay = vm["delay"].as<double>();
            const double weight = vm["weight"].as<double>();
            const double U = vm["U"].as<double>();
            const double u = vm["u"].as<double>();
            const double x = vm["x"].as<double>();
            const double tau_rec = vm["tau_rec"].as<double>();
            const double tau_fac = vm["tau_fac"].as<double>();
            const bool pool = vm["pool"].as<bool>();
            if(pool){
                poormansallocpool.states = pool;
            }
            if ( with_manager ) {
                //build connection manager
                cn = new connectionmanager(vm);
                build_connections_from_neuron(detectors_targetindex, *cn, vm);
            }
            else if ( with_connector ) {
                //build connector
                for(unsigned int i=0; i < num_connections; ++i) {
                    //TODO permute parameters
                    tsodyks2 synapse(delay, weight, U, u, x, tau_rec, tau_fac, detectors_targetindex[i%num_detectors]);
                    conn = add_connection(conn, synapse); //use static function from connectionmanager
                }
            }
            else {
                syn = new tsodyks2(delay, weight, U, u, x, tau_rec, tau_fac, detectors_targetindex[0]);
            }
        }
        /* else if () .. further synapse models*/
        else {
            throw std::invalid_argument("connection model implementation missing");
        }
        //create a few events
        std::vector< spikeevent > events(iterations);
        for (unsigned int i=0; i<iterations; i++) {
            Time t(i*10.0);
            events[i].set_stamp( t ); // in Network::send< SpikeEvent >
            events[i].set_sender( NULL ); // in Network::send< SpikeEvent >
            //events[i]->set_sender_gid( sgid ); // Network::send_local
        }

        boost::chrono::system_clock::duration delay;

        if ( with_manager ) {
            if (cn==NULL) {
                throw std::runtime_error("connectionmanager pointer is not valid");
            }
            const int t = vm["thread"].as<int>(); // thead_num
            const int min_delay=vm["min_delay"].as<int>();
            const int nSpikes = vm["nSpikes"].as<int>();
            const int simtime = iterations * min_delay;
            const int ngroups = vm["nGroups"].as<int>();
            const int rank = vm["rank"].as<int>();
            const int size = vm["size"].as<int>();
            const int ncells = vm["nNeurons"].as<int>();
            //environment::event_generator generator(nSpikes, simtime, ngroups, rank, size, ncells);
            environment::event_generator generator(ngroups);
            double mean = static_cast<double>(simtime) / static_cast<double>(nSpikes);
            double lambda = 1.0 / static_cast<double>(mean * size);
            environment::generate_poisson_events(generator.begin(),
                             simtime, ngroups, rank, size, ncells, lambda);

            const unsigned int stats_generated_spikes = generator.get_size(t);
            int sim_time = 0;
            spikeevent se;
            boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
            for (unsigned int i=0; i<iterations; i++) {
                sim_time+=min_delay;
                while(generator.compare_top_lte(t, sim_time)) {
                    environment::gen_event g = generator.pop(t);
                    index nid = g.first;
                    se.set_stamp( Time(g.second) ); // in Network::send< SpikeEvent >
                    se.set_sender_gid( nid ); // in Network::send< SpikeEvent >

                    cn->send(t, nid, se); //send spike
                }
            }
            delay = boost::chrono::system_clock::now() - start;
            std::cout << "Connection manager simulated" << std::endl;
            std::cout << "Statistics:" << std::endl;
            std::cout << "\tgenerated spikes: " << stats_generated_spikes << std::endl;
            int recvSpikes=0;
            for (unsigned int i=0; i<detectors.size(); i++)
                recvSpikes+=detectors[i].spikes.size();
            std::cout << "\trecv spikes: " << recvSpikes << std::endl;

            std::cout << "\tEvents left:" << std::endl;
            while (!generator.empty(t)) {
                environment::gen_event g = generator.pop(t);
                std::cout << "Event " << g.first << " " << g.second << std::endl;
            }

            delete cn;
        }
        else if ( with_connector ) {
            if (conn==NULL) {
                throw std::runtime_error("connector pointer is not valid");
            }
            boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
            for (unsigned int i=0; i<iterations; i++) {
                conn->send(events[i]); //send spike
            }
            delay = boost::chrono::system_clock::now() - start;

            std::cout << "Connector simulated with " << num_connections << " connections" << std::endl;
        }
        else {
            if (!syn) {
                throw std::runtime_error("connection pointer is not valid");
            }
            double t_lastspike = 0.0;
            boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
            for (unsigned int i=0; i<iterations; i++) {
                syn->send(events[i], t_lastspike); //send spike
                t_lastspike += dt;
            }
            delay = boost::chrono::system_clock::now() - start;
            std::cout << "Single connection simulated" << std::endl;
            delete syn;
        }

        std::cout << "Duration: " << delay << std::endl;
        std::cout << "Last weight " << detectors[0].spikes.back().get_weight() << std::endl;
    }