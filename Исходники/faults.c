void evg_faults_init(void)
{
	FILE *f;
	char line[MAX_STRING_SIZE];
	char *line_ptr;
	struct evg_fault_t *fault;
	int line_num;
	long long last_cycle;

	evg_fault_list = linked_list_create();
	if (!*evg_faults_file_name)
		return;

	f = fopen(evg_faults_file_name, "rt");
	if (!f)
		fatal("%s: cannot open file", evg_faults_file_name);
	
	line_num = 0;
	last_cycle = 0;
	while (!feof(f))
	{
		const char *delim = " ";
	
		/* Read a line */
		line_num++;
		line_ptr = fgets(line, MAX_STRING_SIZE, f);
		if (!line_ptr)
			break;

		/* Allocate new fault */
		fault = calloc(1, sizeof(struct evg_fault_t));
		if (!fault)
			fatal("%s: out of memory", __FUNCTION__);

		/* Read <cycle> field */
		line_ptr = strtok(line_ptr, delim);
		if (!line_ptr)
			goto wrong_format;
		fault->cycle = atoll(line_ptr);
		if (fault->cycle < 1)
			fatal("%s: line %d: lowest possible cycle is 1",
				evg_faults_file_name, line_num);
		if (fault->cycle < last_cycle)
			fatal("%s: line %d: cycles must be ordered",
				evg_faults_file_name, line_num);

		/* <fault> - Type of fault */
		line_ptr = strtok(NULL, delim);
		if (!line_ptr)
			goto wrong_format;
		if (!strcmp(line_ptr, "ams"))
			fault->type = evg_fault_ams;
		else if (!strcmp(line_ptr, "reg"))
			fault->type = evg_fault_reg;
		else if (!strcmp(line_ptr, "mem"))
			fault->type = evg_fault_mem;
		else
			fatal("%s: line %d: invalid value for <fault> ('%s')",
				evg_faults_file_name, line_num, line_ptr);

		/* <cu_id> - Compute unit */
		line_ptr = strtok(NULL, delim);
		if (!line_ptr)
			goto wrong_format;
		fault->compute_unit_id = atoi(line_ptr);
		if (fault->compute_unit_id >= evg_gpu_num_compute_units || fault->compute_unit_id < 0)
			fatal("%s: line %d: invalid compute unit ID",
				evg_faults_file_name, line_num);

		/* Analyze rest of the line depending on fault type */
		switch (fault->type)
		{

		case evg_fault_ams:

			/* <stack_id> - Stack ID */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->stack_id = atoi(line_ptr);
			if (fault->stack_id >= evg_gpu_max_wavefronts_per_compute_unit)
				fatal("%s: line %d: invalid stack ID",
					evg_faults_file_name, line_num);

			/* <am_id> - Active mask ID */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->active_mask_id = atoi(line_ptr);
			if (fault->active_mask_id >= EVG_MAX_STACK_SIZE)
				fatal("%s: line %d: invalid active mask ID",
					evg_faults_file_name, line_num);

			/* <bit> */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->bit = atoi(line_ptr);
			if (fault->bit >= evg_emu_wavefront_size)
				fatal("%s: line %d: invalid bit index",
					evg_faults_file_name, line_num);

			/* No more tokens */
			if (strtok(NULL, delim))
				fatal("%s: line %d: too many arguments",
					evg_faults_file_name, line_num);

			break;

		case evg_fault_reg:

			/* <reg_id> - Register ID */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->reg_id = atoi(line_ptr);
			if (fault->reg_id >= evg_gpu_num_registers || fault->reg_id < 0)
				fatal("%s: line %d: invalid compute unit ID",
					evg_faults_file_name, line_num);

			/* <bit> */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->bit = atoi(line_ptr);
			if (fault->bit < 0 || fault->bit >= 128)
				fatal("%s: line %d: invalid bit index",
					evg_faults_file_name, line_num);

			break;

		case evg_fault_mem:

			/* <byte> - Byte position in local memory */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->byte = atoi(line_ptr);
			if (fault->byte >= evg_gpu_local_mem_size || fault->byte < 0)
				fatal("%s: line %d: invalid byte position",
					evg_faults_file_name, line_num);

			/* <bit> - Bit position */
			line_ptr = strtok(NULL, delim);
			if (!line_ptr)
				goto wrong_format;
			fault->bit = atoi(line_ptr);
			if (fault->bit > 7 || fault->bit < 0)
				fatal("%s: line %d: invalid bit position",
					evg_faults_file_name, line_num);

			break;
		}

		/* Insert fault in fault list */
		linked_list_out(evg_fault_list);
		linked_list_insert(evg_fault_list, fault);
		last_cycle = fault->cycle;
		continue;

wrong_format:
		fatal("%s: line %d: not enough arguments",
			evg_faults_file_name, line_num);
	}
	linked_list_head(evg_fault_list);
}