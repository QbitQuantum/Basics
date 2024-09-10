void
default_pager_initialize(
	mach_port_t host_port)
{
	kern_return_t		kr;
	static char		here[] = "default_pager_initialize";

	/* 
	 * Initial thread and task ports.
	 */
	default_pager_self = mach_task_self();
	default_pager_default_thread = mach_thread_self();

	PRINTF_LOCK_INIT();

	/*
	 * Make ourselves unswappable.
	 */
	kr = task_swappable(default_pager_host_port, default_pager_self, FALSE);
	if (kr != KERN_SUCCESS)
		dprintf(("task_swappable failed 0x%x %s\n",
			 kr, mach_error_string(kr)));

	/*
	 * Exported DMM port.
	 */
	kr = mach_port_allocate(default_pager_self, MACH_PORT_RIGHT_RECEIVE,
				&default_pager_default_port);
	if (kr != KERN_SUCCESS)
		Panic("default port");

	/*
	 * Port sets.
	 */
	kr = mach_port_allocate(default_pager_self, MACH_PORT_RIGHT_PORT_SET,
				&default_pager_internal_set);
	if (kr != KERN_SUCCESS)
		Panic("internal set");

	kr = mach_port_allocate(default_pager_self, MACH_PORT_RIGHT_PORT_SET,
				&default_pager_external_set);
	if (kr != KERN_SUCCESS)
		Panic("external set");

	/*
	 * Export pager interfaces.
	 */
#ifdef	USER_PAGER
	if ((kr = netname_check_in(name_server_port, "UserPager",
				   default_pager_self,
				   default_pager_default_port))
	    != KERN_SUCCESS) {
		dprintf(("netname_check_in returned 0x%x %s\n",
			 kr, mach_error_string(kr)));
		exit(1);
	}
#else	/* USER_PAGER */
	{
		int clsize;
		memory_object_t DMM;

		/* get a send right for vm_set_default_memory_manager */
		kr = mach_port_insert_right(default_pager_self,
					    default_pager_default_port,
					    default_pager_default_port,
					    MACH_MSG_TYPE_MAKE_SEND);
		DMM = default_pager_default_port;
		clsize = (vm_page_size << vstruct_def_clshift);

		kr = host_default_memory_manager(host_port, &DMM, clsize);
		if ((kr != KERN_SUCCESS) || (DMM != MACH_PORT_NULL))
			Panic("default memory manager");

		/* release the extra send right */
		(void) mach_port_mod_refs(default_pager_self,
					  default_pager_default_port,
					  MACH_PORT_RIGHT_SEND,
					  -1);
	}
#endif	/* USER_PAGER */

	kr = mach_port_allocate(default_pager_self, MACH_PORT_RIGHT_PORT_SET,
				&default_pager_default_set);
	if (kr != KERN_SUCCESS)
		Panic("default set");

	kr = mach_port_move_member(default_pager_self,
				   default_pager_default_port,
				   default_pager_default_set);
	if (kr != KERN_SUCCESS)
		Panic("set up default");

	/*
	 * Arrange for wiring privileges.
	 */
	wire_setup(host_port);

	/*
	 * Find out how many CPUs we have, to determine the number
	 * of threads to create.
	 */
	if (default_pager_internal_count == 0) {
		host_basic_info_data_t h_info;
		mach_msg_type_number_t h_info_count;

		h_info_count = HOST_BASIC_INFO_COUNT;
		(void) host_info(host_port, HOST_BASIC_INFO,
				(host_info_t) &h_info, &h_info_count);

		/*
		 * Random computation to get more parallelism on
		 * multiprocessors.
		 */
		default_pager_internal_count = ((h_info.avail_cpus > 32)
						? 32
						: h_info.avail_cpus) / 4 + 3;
	}

	/*
	 * Vm variables.
	 */
	vm_page_mask = vm_page_size - 1;
	vm_page_shift = log2(vm_page_size);

	/*
	 * List of all vstructs.
	 */
	VSL_LOCK_INIT();
	queue_init(&vstruct_list.vsl_queue);
	queue_init(&vstruct_list.vsl_leak_queue);
	vstruct_list.vsl_count = 0;

	VSTATS_LOCK_INIT(&global_stats.gs_lock);

	bs_initialize();
}