int
jack_release_shm_info (jack_shm_registry_index_t index)
{
	/* must NOT have the registry locked */
	if (jack_shm_registry[index].allocator == GetPID()) {
		if (jack_shm_lock_registry () < 0) {
            jack_error ("jack_shm_lock_registry fails...");
            return -1;
        }
		jack_release_shm_entry (index);
		jack_shm_unlock_registry ();
	}

    return 0;
}