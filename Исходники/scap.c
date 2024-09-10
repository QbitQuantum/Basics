scap_t* scap_open_live(char *error)
{
#ifdef _WIN32
	snprintf(error, SCAP_LASTERR_SIZE, "live capture not supported on windows");
	return NULL;
#elif defined(__APPLE__)
	snprintf(error, SCAP_LASTERR_SIZE, "live capture not supported on OSX");
	return NULL;
#else
	uint32_t j;
	char dev[255];
	scap_t* handle = NULL;
	int len;
	uint32_t ndevs;
	uint32_t res;

	//
	// Allocate the handle
	//
	handle = (scap_t*)malloc(sizeof(scap_t));
	if(!handle)
	{
		snprintf(error, SCAP_LASTERR_SIZE, "error allocating the scap_t structure");
		return NULL;
	}

	//
	// Preliminary initializations
	//
	handle->m_ndevs = 0;
	handle->m_proclist = NULL;
	handle->m_file = NULL;
	handle->m_file_evt_buf = NULL;
	handle->m_evtcnt = 0;
	handle->m_addrlist = NULL;
	handle->m_userlist = NULL;
	handle->m_emptybuf_timeout_ms = BUFFER_EMPTY_WAIT_TIME_MS;

	//
	// Find out how many devices we have to open, which equals to the number of CPUs
	//
	ndevs = sysconf(_SC_NPROCESSORS_ONLN);

	//
	// Allocate the device descriptors.
	//
	len = RING_BUF_SIZE * 2;

	handle->m_devs = (scap_device*)malloc(ndevs * sizeof(scap_device));
	if(!handle->m_devs)
	{
		scap_close(handle);
		snprintf(error, SCAP_LASTERR_SIZE, "error allocating the device handles");
		return NULL;
	}

	//
	// Allocate the array of poll fds.
	//
	handle->m_pollfds = (struct pollfd*)malloc(ndevs * sizeof(struct pollfd));
	if(!handle->m_pollfds)
	{
		scap_close(handle);
		snprintf(error, SCAP_LASTERR_SIZE, "error allocating the device handles");
		return NULL;
	}

	for(j = 0; j < ndevs; j++)
	{
		handle->m_devs[j].m_buffer = (char*)MAP_FAILED;
		handle->m_devs[j].m_bufinfo = (struct ppm_ring_buffer_info*)MAP_FAILED;
	}

	handle->m_ndevs = ndevs;

	//
	// Extract machine information
	//
	handle->m_machine_info.num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	handle->m_machine_info.memory_size_bytes = (uint64_t)sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
	gethostname(handle->m_machine_info.hostname, sizeof(handle->m_machine_info.hostname) / sizeof(handle->m_machine_info.hostname[0]));
	handle->m_machine_info.reserved1 = 0;
	handle->m_machine_info.reserved2 = 0;
	handle->m_machine_info.reserved3 = 0;
	handle->m_machine_info.reserved4 = 0;

	//
	// Create the interface list
	//
	if(scap_create_iflist(handle) != SCAP_SUCCESS)
	{
		scap_close(handle);
		snprintf(error, SCAP_LASTERR_SIZE, "error creating the interface list");
		return NULL;
	}

	//
	// Create the user list
	//
	if(scap_create_userlist(handle) != SCAP_SUCCESS)
	{
		scap_close(handle);
		snprintf(error, SCAP_LASTERR_SIZE, "error creating the interface list");
		return NULL;
	}

	//
	// Create the process list
	//
	error[0] = '\0';
	if((res = scap_proc_scan_proc_dir(handle, "/proc", -1, -1, NULL, error, true)) != SCAP_SUCCESS)
	{
		scap_close(handle);
		snprintf(error, SCAP_LASTERR_SIZE, "error creating the process list. Make sure you have root credentials.");
		return NULL;
	}

	handle->m_fake_kernel_proc.tid = -1;
	handle->m_fake_kernel_proc.pid = -1;
	handle->m_fake_kernel_proc.flags = 0;
	snprintf(handle->m_fake_kernel_proc.comm, SCAP_MAX_PATH_SIZE, "kernel");
	snprintf(handle->m_fake_kernel_proc.exe, SCAP_MAX_PATH_SIZE, "kernel");
	handle->m_fake_kernel_proc.args[0] = 0;

	//
	// Open and initialize all the devices
	//
	for(j = 0; j < handle->m_ndevs; j++)
	{
		//
		// Open the device
		//
		sprintf(dev, "/dev/sysdig%d", j);

		if((handle->m_devs[j].m_fd = open(dev, O_RDWR | O_SYNC)) < 0)
		{
			if(errno == EBUSY)
			{
				snprintf(error, SCAP_LASTERR_SIZE, "device %s is already open. You can't run multiple instances of sysdig.", dev);
			}
			else
			{
				snprintf(error, SCAP_LASTERR_SIZE, "error opening device %s. Make sure you have root credentials and that the sysdig-probe module is loaded.", dev);
			}

			scap_close(handle);
			return NULL;
		}

		//
		// Init the polling fd for the device
		//
		handle->m_pollfds[j].fd = handle->m_devs[j].m_fd;
		handle->m_pollfds[j].events = POLLIN;

		//
		// Map the ring buffer
		//
		handle->m_devs[j].m_buffer = (char*)mmap(0,
		                             len,
		                             PROT_READ,
		                             MAP_SHARED,
		                             handle->m_devs[j].m_fd,
		                             0);

		if(handle->m_devs[j].m_buffer == MAP_FAILED)
		{
			// we cleanup this fd and then we let scap_close() take care of the other ones
			close(handle->m_devs[j].m_fd);

			scap_close(handle);

			snprintf(error, SCAP_LASTERR_SIZE, "error mapping the ring buffer for device %s", dev);
			return NULL;
		}

		//
		// Map the ppm_ring_buffer_info that contains the buffer pointers
		//
		handle->m_devs[j].m_bufinfo = (struct ppm_ring_buffer_info*)mmap(0,
		                              sizeof(struct ppm_ring_buffer_info),
		                              PROT_READ | PROT_WRITE,
		                              MAP_SHARED,
		                              handle->m_devs[j].m_fd,
		                              0);

		if(handle->m_devs[j].m_bufinfo == MAP_FAILED)
		{
			// we cleanup this fd and then we let scap_close() take care of the other ones
			munmap(handle->m_devs[j].m_buffer, len);
			close(handle->m_devs[j].m_fd);

			scap_close(handle);

			snprintf(error, SCAP_LASTERR_SIZE, "error mapping the ring buffer info for device %s", dev);
			return NULL;
		}

		//
		// Additional initializations
		//
		handle->m_devs[j].m_lastreadsize = 0;
		handle->m_devs[j].m_sn_len = 0;
		scap_stop_dropping_mode(handle);
	}

	return handle;
#endif // _WIN32
}