	void host_object::test<9>()
	{
//		skip("setHostByName(\"google.com\"); getHostName() -> (e.g.) \"yx-in-f100.1e100.net\"");
		std::string hostStr = "linux.org";		
		LLHost host;
		host.setHostByName(hostStr);	

		// reverse DNS will likely result in appending of some
		// sub-domain to the main hostname. so look for
		// the main domain name and not do the exact compare
		
		std::string hostname = host.getHostName();
		try
		{
			ensure("getHostName failed", hostname.find(hostStr) != std::string::npos);
		}
		catch (const std::exception&)
		{
			std::cerr << "set '" << hostStr << "'; reported '" << hostname << "'" << std::endl;
			throw;
		}
	}