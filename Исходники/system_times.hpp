	bool get_times_since_last_call(float &idle_frac, float &kernel_frac, float &user_frac) {
		std::uint64_t idle, kernel, user;

#ifdef _MSC_VER
		if (!GetSystemTimes(reinterpret_cast<PFILETIME>(&idle),
						   reinterpret_cast<PFILETIME>(&kernel),
						   reinterpret_cast<PFILETIME>(&user)))
			return false;
#elif defined _linux
		FILE *fstat = fopen("/proc/stat", "r");
		if (fstat == NULL) {
			perror("fopen(\"/proc/stat\") failed");
			return 0;
		}
		
		long unsigned int cpu_time[7];
		if (std::fscanf(fstat, "%*s %lu %lu %lu %lu %lu %lu %lu",
						&cpu_time[0], &cpu_time[1], &cpu_time[2], &cpu_time[3],
						&cpu_time[4], &cpu_time[5], &cpu_time[6]) == EOF) {
			fclose(fstat);
			return 0;
		}
		fclose(fstat);
		
		user 	= cpu_time[0] + cpu_time[1];
		kernel 	= cpu_time[2] + cpu_time[5] + cpu_time[6];
		idle 	= cpu_time[3] + cpu_time[4];
#endif

		auto d_user = user - old_user;
		auto d_kernel = kernel - old_kernel;
		auto d_idle = idle - old_idle;
		if (!d_user)
			return false;
		float total = static_cast<float>(d_user + d_kernel + d_idle);
		idle_frac = static_cast<float>(d_idle) / total;
		kernel_frac = static_cast<float>(d_kernel) / total;
		user_frac = static_cast<float>(d_user) / total;

		old_idle = idle;
		old_kernel = kernel;
		old_user = user;

		return true;
	}