int main(int argc, char * argv[]){
	// declaring and initializing some variables. Most of them will be set according to command line options passed to the program after parsing of command line arguments. However, if Boost is not used, the only available command line option is the number of events to generate; other variables will use the values set below
	std::size_t nevents = 0; // number of events to generate
	std::string pythia_cfgfile = "Z2uubar.cmnd"; // name of PYTHIA cofiguration file
	std::string output_filename = "Z2uubar.root"; // name of the output file
	bool verbose = false; // increased verbosity switch

	#ifdef USE_BOOST
		try {
			boost::program_options::options_description desc("Usage");

			// defining command line options. See boost::program_options documentation for more details
			desc.add_options()
							("help", "produce this help message")
							("nevents,n", boost::program_options::value<std::size_t>(&nevents), "number of events to generate")
							("pythiacfg,P", boost::program_options::value<std::string>(&pythia_cfgfile)->default_value("Z2uubar.cmnd"), "PYTHIA config file")
							("outfile,o", boost::program_options::value<std::string>(&output_filename)->default_value("Z2uubar.root"), "Output file")
							("verbose,v", boost::program_options::bool_switch()->default_value(false), "Run with increased verbosity")
			;
			boost::program_options::variables_map vm;
			boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
			boost::program_options::notify(vm);

			if(vm.find("help") != vm.end() || argc < 2) {
				std::cout << "Generator of inclusive events. Version " << Generator_VERSION_MAJOR << '.' << Generator_VERSION_MINOR << std::endl;
				std::cout << desc << std::endl;

				return EXIT_SUCCESS;
			}

			verbose = vm.at("verbose").as<bool>();
		} catch(std::exception const & e) {
			std::cout << e.what() << std::endl;

			return EXIT_FAILURE;
		}
	#else
		if(argc < 2) {
			std::cout << "Generator of inclusive events. Version " << Generator_VERSION_MAJOR << '.' << Generator_VERSION_MINOR << std::endl;
			std::cout << "Usage: " << argv[0] << " n, where \"n\" is a number of events to generate" << std::endl;
			std::cout << "WARNING! This version of the generator does not use program options parser, which means that you are personally responsible for providing correct options to this program." << std::endl;

			return EXIT_SUCCESS;
		} else {
			nevents = std::stoull(argv[1]);
		}
	#endif

	auto start_time = std::chrono::system_clock::now();
	auto last_timestamp = start_time;

	if(verbose) {
			std::cout << "PYTHIA config file: \"" << pythia_cfgfile << "\"" << std::endl << nevents << " events will be generated." << std:: endl;
	}

	if(verbose) {
		std::cout << "Prepairing data store" << std::endl;
	}

	// prepairing event store
	podio::EventStore store;
	podio::ROOTWriter writer(output_filename, &store);

	// registering collections
	auto & evinfocoll = store.create<fcc::EventInfoCollection>("EventInfo");
	auto & pcoll = store.create<fcc::MCParticleCollection>("GenParticle");
	auto & vcoll = store.create<fcc::GenVertexCollection>("GenVertex");

	writer.registerForWrite<fcc::EventInfoCollection>("EventInfo");
	writer.registerForWrite<fcc::MCParticleCollection>("GenParticle");
	writer.registerForWrite<fcc::GenVertexCollection>("GenVertex");

	if(verbose) {
		std::cout << "Initializing PYTHIA" << std::endl;
	}

	// initializing PYTHIA
	Pythia8::Pythia pythia; // creating PYTHIA generator object
	pythia.readFile(pythia_cfgfile); // reading settings from file

	pythia.init(); // initializing PYTHIA generator

	// Interface for conversion from Pythia8::Event to HepMC event.
	HepMC::Pythia8ToHepMC ToHepMC;

	std::size_t counter = 0; // number of "interesting" (that satisfy all the requirements) events generated so far
	std::size_t total = 0; // total number of events generated so far

	if(verbose) {
		std::cout << "Starting to generate events" << std::endl;
	}

	std::map<std::size_t, std::size_t> stable_ptcs_count;

	while(counter < nevents) {
		if(pythia.next()) {
			++total;

			// creating HepMC event storage
			HepMC::GenEvent * hepmcevt = new HepMC::GenEvent(HepMC::Units::GEV, HepMC::Units::MM);

			// converting generated event to HepMC format
			ToHepMC.fill_next_event(pythia, hepmcevt);

			auto nstable = std::count_if(hepmcevt->particles_begin(), hepmcevt->particles_end(), [](HepMC::GenParticle const * const ptc_ptr) {return ptc_ptr->status() == 1;});

			if(nstable <= 7) {
				stable_ptcs_count[nstable]++;
				++counter;

				if(verbose && counter % 100 == 0) {
					std::cout << counter << " events with with 7 or less particles in the final state have been generated (" << total << " total). " << std::chrono::duration<double>(std::chrono::system_clock::now() - last_timestamp).count() / 100 << "events / sec" << std::endl;
					last_timestamp = std::chrono::system_clock::now();
				}

				// filling event info
				auto evinfo = fcc::EventInfo();
				evinfo.Number(counter); // Number takes int as its parameter, so here's a narrowing conversion (std::size_t to int). Should be safe unless we get 2^32 events or more. Then undefined behaviour
				evinfocoll.push_back(evinfo);

				// filling vertices
				std::unordered_map<HepMC::GenVertex *, fcc::GenVertex> vtx_map;
				for(auto iv = hepmcevt->vertices_begin(), endv = hepmcevt->vertices_end(); iv != endv; ++iv) {
					auto vtx = fcc::GenVertex();
					vtx.Position().X = (*iv)->position().x();
					vtx.Position().Y = (*iv)->position().y();
					vtx.Position().Z = (*iv)->position().z();
					vtx.Ctau((*iv)->position().t());
					vtx_map.emplace(*iv, vtx);

					vcoll.push_back(vtx);
				}

				// filling particles
				for(auto ip = hepmcevt->particles_begin(), endp = hepmcevt->particles_end(); ip != endp; ++ip) {
					auto ptc = fcc::MCParticle();
					auto & core = ptc.Core();
					core.Type = (*ip)->pdg_id();
					core.Status = (*ip)->status();

					core.Charge = pythia.particleData.charge(core.Type); // PYTHIA returns charge as a double value (in case it's quark), so here's a narrowing conversion (double to int), but here it's safe
					core.P4.Mass = (*ip)->momentum().m();
					core.P4.Px = (*ip)->momentum().px();
					core.P4.Py = (*ip)->momentum().py();
					core.P4.Pz = (*ip)->momentum().pz();

					auto prodvtx = vtx_map.find((*ip)->production_vertex());
					if(prodvtx != vtx_map.end()) {
						ptc.StartVertex(prodvtx->second);
					}
					auto endvtx = vtx_map.find((*ip)->end_vertex());
					if(endvtx != vtx_map.end()) {
						ptc.EndVertex(endvtx->second);
					}

					pcoll.push_back(ptc);
				}

				writer.writeEvent();
				store.clearCollections();
			}

			// freeing resources
			if(hepmcevt) {
				delete hepmcevt;
				hepmcevt = nullptr;
			}
		}
	}

	writer.finish();

	std::cout << counter << " events with 7 or less particles in the final state have been generated (" << total << " total)." << std::endl;
	for(auto const & nv : stable_ptcs_count) {
		std::cout << std::setw(4) << std::right << nv.first << std::setw(4) << std::right << nv.second << "(" << static_cast<long double>(nv.second) * static_cast<long double>(100) / static_cast<long double>(total) << "%)" << std::endl;
	}
	auto elapsed_seconds = std::chrono::duration<double>(std::chrono::system_clock::now() - start_time).count();
	std::cout << "Elapsed time: " << elapsed_seconds << " s (" << static_cast<long double>(counter) / static_cast<long double>(elapsed_seconds) << " events / s)" << std::endl;

	return EXIT_SUCCESS;
}