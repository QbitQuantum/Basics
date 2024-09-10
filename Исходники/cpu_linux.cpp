void cpu_linux::measurement_end(void)
{
	DIR *dir;
	struct dirent *entry;
	char filename[256];
	ifstream file;
	int len;

	len = sprintf(filename, "/sys/devices/system/cpu/cpu%i/cpuidle", number);

	dir = opendir(filename);
	if (!dir)
		return;

	/* For each C-state, there is a stateX directory which
	 * contains a 'usage' and a 'time' (duration) file */
	while ((entry = readdir(dir))) {
		char linux_name[64];
		char human_name[64];
		uint64_t usage = 0;
		uint64_t duration = 0;


		if (strlen(entry->d_name) < 3)
			continue;

		strcpy(linux_name, entry->d_name);
		strcpy(human_name, linux_name);


		sprintf(filename + len, "/%s/usage", entry->d_name);
		file.open(filename, ios::in);
		if (file) {
			file >> usage;
			file.close();
		}

		sprintf(filename + len, "/%s/time", entry->d_name);

		file.open(filename, ios::in);
		if (file) {
			file >> duration;
			file.close();
		}


		finalize_cstate(linux_name, usage, duration, 1);

	}
	closedir(dir);

	sprintf(filename, "/sys/devices/system/cpu/cpu%i/cpufreq/stats/time_in_state", number);

	file.open(filename, ios::in);

	if (file) {
		char line[1024];

		while (file) {
			uint64_t f,count;
			char *c;

			memset(line, 0, 1024);

			file.getline(line, 1024);

			f = strtoull(line, &c, 10);
			if (!c)
				break;

			count = strtoull(c, NULL, 10);

			if (f > 0)
				finalize_pstate(f, count, 1);


		}
		file.close();
	}


	abstract_cpu::measurement_end();
}