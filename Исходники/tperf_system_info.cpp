	int SystemInfo::get_io_usage(io_info_t& info){
#	ifdef __TPERF_PLATFORM_WINDOWS__
		IO_COUNTERS io;
		if (GetProcessIoCounters(GetCurrentProcess(),&io)){
			info.read_bytes = io.ReadOperationCount;
			info.write_bytes = io.WriteTransferCount;
		}
		return -1;
#	else
		return -1;
#endif 
	}