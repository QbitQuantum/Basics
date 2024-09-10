	bool ProcessMetrics::GetIOCounters(IoCounters* io_counters) const {
		return GetProcessIoCounters(process_, io_counters) != FALSE;
	}