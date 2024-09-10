int main(int argc, char * argv[])
{
    std::cout << "\n Intel(r) Performance Counter Monitor " << INTEL_PCM_VERSION << std::endl;
    std::cout << "\n MSR read/write utility\n\n";
    
    uint64 value = 0;
    bool write = false;
    int core = 0;
    int msr = -1;
    bool dec = false;

	int my_opt = -1;
	while ((my_opt = getopt(argc, argv, "w:c:d")) != -1)
	{
		switch(my_opt)
		{
			case 'w':
                                write = true;
				value = read_number(optarg);
				break;
			case 'c':
				core = (int) read_number(optarg);
				break;
                        case 'd':
                                dec = true;
                                break;
			default:
				print_usage(argv[0]);
				return -1;
		}
	}

	 if (optind >= argc)
	 {
		 print_usage(argv[0]);
		 return -1;
	 }

    msr = (int) read_number(argv[optind]);

    #ifdef OK_WIN_BUILD
    // Increase the priority a bit to improve context switching delays on Windows
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

    TCHAR driverPath[1032];
    GetCurrentDirectory(1024, driverPath);
    wcscat_s(driverPath, 1032, L"\\msr.sys");

    // WARNING: This driver code (msr.sys) is only for testing purposes, not for production use
    Driver drv;
    // drv.stop();     // restart driver (usually not needed)
    if (!drv.start(driverPath))
    {
		std::cout << "Can not load MSR driver." << std::endl;
		std::cout << "You must have signed msr.sys driver in your current directory and have administrator rights to run this program" << std::endl;
        return -1;
    }
    #endif

    MsrHandle h(core);
    if(!dec) std::cout << std::hex << std::showbase;
    if(write)
    {
        std::cout << " Writing "<< value << " to MSR "<< msr << " on core "<< core << std::endl;
        h.write(msr,value);
    }
    value = 0;
    h.read(msr,&value);
    std::cout << " Read value "<< value << " from MSR "<< msr << " on core "<< core << "\n" << std::endl;
}