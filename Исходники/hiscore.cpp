/* call hiscore_open once after loading a game */
void hiscore_init (running_machine &machine)
{
	memory_range *mem_range = state.mem_range;
	address_space *initspace;
	file_error filerr;
  	const char *name = machine.system().name;
	state.hiscores_have_been_loaded = 0;

	while (mem_range)
	{
		if (strstr(machine.system().source_file,"cinemat.c") > 0)
		{
			initspace = &machine.cpu[mem_range->cpu]->memory().space(AS_DATA);
			initspace->write_byte(mem_range->addr, ~mem_range->start_value);
			initspace->write_byte(mem_range->addr + mem_range->num_bytes-1, ~mem_range->end_value);
			mem_range = mem_range->next;
		}
		else
		{
			initspace = &machine.cpu[mem_range->cpu]->memory().space(AS_PROGRAM);
			initspace->write_byte(mem_range->addr, ~mem_range->start_value);
		  	initspace->write_byte(mem_range->addr + mem_range->num_bytes-1, ~mem_range->end_value);
			mem_range = mem_range->next;
		}
	}

	state.mem_range = nullptr;
	emu_file f(machine.options().high_path(), OPEN_FLAG_READ);
  	filerr = f.open("hiscore.dat");

	if (filerr == FILERR_NONE)
	{
		char buffer[MAX_CONFIG_LINE_SIZE];
		enum { FIND_NAME, FIND_DATA, FETCH_DATA } mode;
		mode = FIND_NAME;

		while (f.gets(buffer, MAX_CONFIG_LINE_SIZE))
		{
			if (mode == FIND_NAME)
			{
				if (matching_game_name (buffer, name))
					mode = FIND_DATA;
			}
			else if (is_mem_range (buffer))
			{
				const char *pBuf = buffer;
				mem_range = (memory_range *)malloc(sizeof(memory_range));

				if (mem_range)
				{
					mem_range->cpu = hexstr2num (&pBuf);
					mem_range->addr = hexstr2num (&pBuf);
					mem_range->num_bytes = hexstr2num (&pBuf);
					mem_range->start_value = hexstr2num (&pBuf);
					mem_range->end_value = hexstr2num (&pBuf);

					mem_range->next = nullptr;
					{
						memory_range *last = state.mem_range;
						while (last && last->next) last = last->next;

						if (last == nullptr)
							state.mem_range = mem_range;
						else
							last->next = mem_range;
					}

					mode = FETCH_DATA;
				}
				else
				{
					hiscore_free();
					break;
				}
			}
			else
			{
				/* line is a game name */
				if (mode == FETCH_DATA) 
					break;
			}
		}
		
		f.close();
	}
	
	timer = machine.scheduler().timer_alloc(FUNC(hiscore_periodic));
	timer->adjust(machine.first_screen()->frame_period(), 0, machine.first_screen()->frame_period());

	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(hiscore_close), &machine));
}