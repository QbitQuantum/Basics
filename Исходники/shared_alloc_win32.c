static int zend_shared_alloc_reattach(size_t requested_size, char **error_in)
{
	int err;
	void *wanted_mapping_base;
	char *mmap_base_file = get_mmap_base_file();
	FILE *fp = fopen(mmap_base_file, "r");
	MEMORY_BASIC_INFORMATION info;

	err = GetLastError();
	if (!fp) {
		zend_win_error_message(ACCEL_LOG_WARNING, mmap_base_file, err);
		zend_win_error_message(ACCEL_LOG_FATAL, "Unable to open base address file", err);
		*error_in="fopen";
		return ALLOC_FAILURE;
	}
	if (!fscanf(fp, "%p", &wanted_mapping_base)) {
		err = GetLastError();
		zend_win_error_message(ACCEL_LOG_FATAL, "Unable to read base address", err);
		*error_in="read mapping base";
		fclose(fp);
		return ALLOC_FAILURE;
	}
	fclose(fp);

	/* Check if the requested address space is free */
	if (VirtualQuery(wanted_mapping_base, &info, sizeof(info)) == 0 ||
	    info.State != MEM_FREE ||
	    info.RegionSize < requested_size) {
	    err = ERROR_INVALID_ADDRESS;
		zend_win_error_message(ACCEL_LOG_FATAL, "Unable to reattach to base address", err);
		return ALLOC_FAILURE;
   	}

	mapping_base = MapViewOfFileEx(memfile, FILE_MAP_ALL_ACCESS, 0, 0, 0, wanted_mapping_base);
	err = GetLastError();

	if (mapping_base == NULL) {
		if (err == ERROR_INVALID_ADDRESS) {
			zend_win_error_message(ACCEL_LOG_FATAL, "Unable to reattach to base address", err);
			return ALLOC_FAILURE;
		}
		return ALLOC_FAIL_MAPPING;
	}
	smm_shared_globals = (zend_smm_shared_globals *) mapping_base;

	return SUCCESSFULLY_REATTACHED;
}