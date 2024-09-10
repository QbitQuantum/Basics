void runTest(const char* path)
{
	/*
	std::string line;
	g_shell->out() << "echo Hello world\n" << std::flush;
	std::getline(g_shell->in(), line);

	termcolor::set(termcolor::RED);
	std::cout << line << std::endl;
	termcolor::reset();
	*/
	
	std::stringstream cmd;
	std::string binary;
	std::string out, err;
	std::string filename = "/tmp/";
	int rv;

	filename += uniqueName(path);

	binary = stripext(filename);
	
	termcolor::set(termcolor::WHITE, termcolor::BLACK, termcolor::DIM);

	std::cout << "Uploading " << path << "...\n";
	// upload the source code
	g_sftp->upload(path, filename);

	try
	{
		std::cout << "Compiling...\n";
		// compile the code remotely
		cmd << compiler(path) << ' ' << cflags(path) << filename << " -o " << binary;
		rv = g_ssh->runCommand(cmd.str(), out, err);

		if (rv)
			throw compile_error(err);

		std::cout << "Running remotely...\n";
		// run the program remotely
		rv = g_ssh->runCommand(binary, out, err);
		
		if (rv)
			throw nonzero_exit_error(true, out);

		std::cout << "Downloading...\n";
		// download the Mach-O executable
		g_sftp->download(binary, binary);

		std::cout << "Running locally...\n";
		// run the executable via dyld
		std::stringstream locOut;
		pstream* loc = pstream::popen(std::string(DYLD_COMMAND) + " " + binary);

		locOut << loc;
		
		rv = loc->wait();
		
		if (rv)
			throw nonzero_exit_error(false, locOut.str());

		if (locOut.str() != out)
			throw different_output_error(out, locOut.str());
	}
	catch (...)
	{
		// clean up locally
		unlink(binary.c_str());

		try
		{
			// clean up remotely
			g_sftp->unlink(binary);
			g_sftp->unlink(filename);
		}
		catch (...) {}

		throw;
	}
}