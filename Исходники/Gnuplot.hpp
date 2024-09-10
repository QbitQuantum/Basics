	explicit Gnuplot(const std::string cmd = "gnuplot") : 
					 boost::iostreams::stream<boost::iostreams::file_descriptor_sink>(
					 FILENO(pout = POPEN(cmd.c_str(), "w")),
					 boost::iostreams::never_close_handle),
					 pout(pout), // keeps '-Weff++' quiet
					 gp_pty(NULL),
					 debug_messages(false)
	{
		*this << std::scientific << std::setprecision(18);  // refer <iomanip>
	}