static int
task_main(int argc, char *argv[])
{
	work_q_item_t *work;

	/* inform about start */
	warnx("Initializing..");

	/* Initialize global variables */
	g_key_offsets[0] = 0;

	for (unsigned i = 0; i < (DM_KEY_NUM_KEYS - 1); i++)
		g_key_offsets[i + 1] = g_key_offsets[i] + (g_per_item_max_index[i] * k_sector_size);

	unsigned max_offset = g_key_offsets[DM_KEY_NUM_KEYS - 1] + (g_per_item_max_index[DM_KEY_NUM_KEYS - 1] * k_sector_size);

	for (unsigned i = 0; i < dm_number_of_funcs; i++)
		g_func_counts[i] = 0;

	/* Initialize the item type locks, for now only DM_KEY_MISSION_STATE supports locking */
	sem_init(&g_sys_state_mutex, 1, 1); /* Initially unlocked */
	for (unsigned i = 0; i < DM_KEY_NUM_KEYS; i++)
		g_item_locks[i] = NULL;
	g_item_locks[DM_KEY_MISSION_STATE] = &g_sys_state_mutex;

	g_task_should_exit = false;

	init_q(&g_work_q);
	init_q(&g_free_q);

	sem_init(&g_work_queued_sema, 1, 0);

	/* See if the data manage file exists and is a multiple of the sector size */
	g_task_fd = open(k_data_manager_device_path, O_RDONLY | O_BINARY);
	if (g_task_fd >= 0) {
		/* File exists, check its size */
		int file_size = lseek(g_task_fd, 0, SEEK_END);
		if ((file_size % k_sector_size) != 0) {
			warnx("Incompatible data manager file %s, resetting it", k_data_manager_device_path);
			close(g_task_fd);
			unlink(k_data_manager_device_path);
		}
		else
			close(g_task_fd);
	}

	/* Open or create the data manager file */
	g_task_fd = open(k_data_manager_device_path, O_RDWR | O_CREAT | O_BINARY);

	if (g_task_fd < 0) {
		warnx("Could not open data manager file %s", k_data_manager_device_path);
		sem_post(&g_init_sema); /* Don't want to hang startup */
		return -1;
	}

	if ((unsigned)lseek(g_task_fd, max_offset, SEEK_SET) != max_offset) {
		close(g_task_fd);
		warnx("Could not seek data manager file %s", k_data_manager_device_path);
		sem_post(&g_init_sema); /* Don't want to hang startup */
		return -1;
	}

	fsync(g_task_fd);

	/* see if we need to erase any items based on restart type */
	int sys_restart_val;
	if (param_get(param_find("SYS_RESTART_TYPE"), &sys_restart_val) == OK) {
		if (sys_restart_val == DM_INIT_REASON_POWER_ON) {
			warnx("Power on restart");
			_restart(DM_INIT_REASON_POWER_ON);
		}
		else if (sys_restart_val == DM_INIT_REASON_IN_FLIGHT) {
			warnx("In flight restart");
			_restart(DM_INIT_REASON_IN_FLIGHT);
		}
		else
			warnx("Unknown restart");
	}
	else
		warnx("Unknown restart");

	/* We use two file descriptors, one for the caller context and one for the worker thread */
	/* They are actually the same but we need to some way to reject caller request while the */
	/* worker thread is shutting down but still processing requests */
	g_fd = g_task_fd;

	warnx("Initialized, data manager file '%s' size is %d bytes", k_data_manager_device_path, max_offset);

	/* Tell startup that the worker thread has completed its initialization */
	sem_post(&g_init_sema);

	/* Start the endless loop, waiting for then processing work requests */
	while (true) {

		/* do we need to exit ??? */
		if ((g_task_should_exit) && (g_fd >= 0)) {
			/* Close the file handle to stop further queuing */
			g_fd = -1;
		}

		if (!g_task_should_exit) {
			/* wait for work */
			sem_wait(&g_work_queued_sema);
		}

		/* Empty the work queue */
		while ((work = dequeue_work_item())) {

			/* handle each work item with the appropriate handler */
			switch (work->func) {
			case dm_write_func:
				g_func_counts[dm_write_func]++;
				work->result =
					_write(work->write_params.item, work->write_params.index, work->write_params.persistence, work->write_params.buf, work->write_params.count);
				break;

			case dm_read_func:
				g_func_counts[dm_read_func]++;
				work->result =
					_read(work->read_params.item, work->read_params.index, work->read_params.buf, work->read_params.count);
				break;

			case dm_clear_func:
				g_func_counts[dm_clear_func]++;
				work->result = _clear(work->clear_params.item);
				break;

			case dm_restart_func:
				g_func_counts[dm_restart_func]++;
				work->result = _restart(work->restart_params.reason);
				break;

			default: /* should never happen */
				work->result = -1;
				break;
			}

			/* Inform the caller that work is done */
			sem_post(&work->wait_sem);
		}

		/* time to go???? */
		if ((g_task_should_exit) && (g_fd < 0))
			break;
	}

	close(g_task_fd);
	g_task_fd = -1;

	/* The work queue is now empty, empty the free queue */
	for (;;) {
		if ((work = (work_q_item_t *)sq_remfirst(&(g_free_q.q))) == NULL)
			break;
		if (work->first)
			free(work);
	}

	destroy_q(&g_work_q);
	destroy_q(&g_free_q);
	sem_destroy(&g_work_queued_sema);
	sem_destroy(&g_sys_state_mutex);

	return 0;
}