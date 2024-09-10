acpi_status
bm_initialize (void)
{
	acpi_status             status = AE_OK;
	u32                     start = 0;
	u32                     stop = 0;
	u32                     elapsed = 0;

	FUNCTION_TRACE("bm_initialize");

	MEMSET(&node_list, 0, sizeof(BM_NODE_LIST));

	status = acpi_get_timer(&start);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Building device hierarchy.\n"));

	/*
	 * Enumerate ACPI fixed-feature devices.
	 */
	status = bm_enumerate_fixed_features();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * Enumerate the ACPI namespace.
	 */
	status = bm_enumerate_namespace();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	acpi_get_timer(&stop);
	acpi_get_timer_duration(start, stop, &elapsed);

	ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Building device hierarchy took [%d] microseconds.\n", elapsed));

	/*
	 * Display hierarchy.
	 */
	bm_print_hierarchy();

	/*
	 * Register for all standard and device-specific notifications.
	 */
	ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Registering for all device notifications.\n"));

	status = acpi_install_notify_handler(ACPI_ROOT_OBJECT,
		ACPI_SYSTEM_NOTIFY, &bm_notify, NULL);
	if (ACPI_FAILURE(status)) {
		ACPI_DEBUG_PRINT ((ACPI_DB_ERROR, "Unable to register for standard notifications.\n"));
		return_ACPI_STATUS(status);
	}

	status = acpi_install_notify_handler(ACPI_ROOT_OBJECT,
		ACPI_DEVICE_NOTIFY, &bm_notify, NULL);
	if (ACPI_FAILURE(status)) {
		ACPI_DEBUG_PRINT ((ACPI_DB_ERROR, "Unable to register for device-specific notifications.\n"));
		return_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "ACPI Bus Manager enabled.\n"));

	/*
	 * Initialize built-in power resource driver.
	 */
	bm_pr_initialize();

	return_ACPI_STATUS(status);
}