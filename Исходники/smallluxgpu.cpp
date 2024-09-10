int main(int argc, char *argv[]) {
#if defined(__GNUC__) && !defined(__CYGWIN__)
	set_terminate(SLGTerminate);
#endif

	// This is required to run AMD GPU profiler
	//XInitThreads();

	luxrays::sdl::LuxRaysSDLDebugHandler = SDLDebugHandler;

	try {
		// Initialize FreeImage Library
		FreeImage_Initialise(TRUE);
		FreeImage_SetOutputMessage(FreeImageErrorHandler);

		bool batchMode = false;
		bool telnetServerEnabled = false;
		Properties cmdLineProp;
		string configFileName;
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == '-') {
				// I should check for out of range array index...

				if (argv[i][1] == 'h') {
					SLG_LOG("Usage: " << argv[0] << " [options] [configuration file]" << endl <<
							" -o [configuration file]" << endl <<
							" -f [scene file]" << endl <<
							" -w [window width]" << endl <<
							" -e [window height]" << endl <<
							" -t [halt time in secs]" << endl <<
							" -T <enable the telnet server>" << endl <<
							" -D [property name] [property value]" << endl <<
							" -d [current directory path]" << endl <<
							" -m Makes the mouse operations work in \"grab mode\"" << endl << 
							" -h <display this help and exit>");
					exit(EXIT_SUCCESS);
				}
				else if (argv[i][1] == 'o') {
					if (configFileName.compare("") != 0)
						throw runtime_error("Used multiple configuration files");

					configFileName = string(argv[++i]);
				}

				else if (argv[i][1] == 'e') cmdLineProp.SetString("image.height", argv[++i]);

				else if (argv[i][1] == 'w') cmdLineProp.SetString("image.width", argv[++i]);

				else if (argv[i][1] == 'f') cmdLineProp.SetString("scene.file", argv[++i]);

				else if (argv[i][1] == 't') cmdLineProp.SetString("batch.halttime", argv[++i]);

				else if (argv[i][1] == 'T') telnetServerEnabled = true;

				else if (argv[i][1] == 'm') mouseGrabMode = true;

				else if (argv[i][1] == 'D') {
					cmdLineProp.SetString(argv[i + 1], argv[i + 2]);
					i += 2;
				}

				else if (argv[i][1] == 'd') boost::filesystem::current_path(boost::filesystem::path(argv[++i]));

				else {
					SLG_LOG("Invalid option: " << argv[i]);
					exit(EXIT_FAILURE);
				}
			} else {
				string s = argv[i];
				if ((s.length() >= 4) && (s.substr(s.length() - 4) == ".cfg")) {
					if (configFileName.compare("") != 0)
						throw runtime_error("Used multiple configuration files");
					configFileName = s;
				} else
					throw runtime_error("Unknown file extension: " + s);
			}
		}

		if (configFileName.compare("") == 0)
			configFileName = "scenes/luxball/luxball.cfg";

		RenderConfig *config = new RenderConfig(&configFileName, &cmdLineProp);

		const unsigned int halttime = config->cfg.GetInt("batch.halttime", 0);
		const unsigned int haltspp = config->cfg.GetInt("batch.haltspp", 0);
		const float haltthreshold = config->cfg.GetFloat("batch.haltthreshold", -1.f);
		if ((halttime > 0) || (haltspp > 0) || (haltthreshold >= 0.f))
			batchMode = true;
		else
			batchMode = false;

		if (batchMode) {
			session = new RenderSession(config);

			// Check if I have to do tile rendering
			if (config->cfg.IsDefined("batch.tile"))
				return BatchTileMode(haltspp, haltthreshold);
			else
				return BatchSimpleMode(halttime, haltspp, haltthreshold);
		} else {
			// It is important to initialize OpenGL before OpenCL
			// (for OpenGL/OpenCL inter-operability)
			u_int width, height;
			config->GetScreenSize(&width, &height);
			InitGlut(argc, argv, width, height);

			session = new RenderSession(config);

			// Start the rendering
			session->Start();

			if (telnetServerEnabled) {
				TelnetServer telnetServer(18081, session);
				RunGlut();
			} else
				RunGlut();
		}
#if !defined(LUXRAYS_DISABLE_OPENCL)
	} catch (cl::Error err) {
		SLG_LOG("OpenCL ERROR: " << err.what() << "(" << luxrays::utils::oclErrorString(err.err()) << ")");
		return EXIT_FAILURE;
#endif
	} catch (runtime_error err) {
		SLG_LOG("RUNTIME ERROR: " << err.what());
		return EXIT_FAILURE;
	} catch (exception err) {
		SLG_LOG("ERROR: " << err.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}