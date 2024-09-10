acpi_status
acpi_get_object_info (
	acpi_handle             handle,
	acpi_device_info        *info)
{
	acpi_device_id          hid;
	acpi_device_id          uid;
	acpi_status             status;
	u32                     device_status = 0;
	acpi_integer            address = 0;
	acpi_namespace_node     *node;


	/* Parameter validation */

	if (!handle || !info) {
		return (AE_BAD_PARAMETER);
	}

	acpi_ut_acquire_mutex (ACPI_MTX_NAMESPACE);

	node = acpi_ns_map_handle_to_node (handle);
	if (!node) {
		acpi_ut_release_mutex (ACPI_MTX_NAMESPACE);
		return (AE_BAD_PARAMETER);
	}

	info->type      = node->type;
	info->name      = node->name;

	acpi_ut_release_mutex (ACPI_MTX_NAMESPACE);

	/*
	 * If not a device, we are all done.
	 */
	if (info->type != ACPI_TYPE_DEVICE) {
		return (AE_OK);
	}


	/*
	 * Get extra info for ACPI devices only.  Run the
	 * _HID, _UID, _STA, and _ADR methods.  Note: none
	 * of these methods are required, so they may or may
	 * not be present.  The Info->Valid bits are used
	 * to indicate which methods ran successfully.
	 */
	info->valid = 0;

	/* Execute the _HID method and save the result */

	status = acpi_ut_execute_HID (node, &hid);
	if (ACPI_SUCCESS (status)) {
		STRNCPY (info->hardware_id, hid.buffer, sizeof(info->hardware_id));

		info->valid |= ACPI_VALID_HID;
	}

	/* Execute the _UID method and save the result */

	status = acpi_ut_execute_UID (node, &uid);
	if (ACPI_SUCCESS (status)) {
		STRCPY (info->unique_id, uid.buffer);

		info->valid |= ACPI_VALID_UID;
	}

	/*
	 * Execute the _STA method and save the result
	 * _STA is not always present
	 */
	status = acpi_ut_execute_STA (node, &device_status);
	if (ACPI_SUCCESS (status)) {
		info->current_status = device_status;
		info->valid |= ACPI_VALID_STA;
	}

	/*
	 * Execute the _ADR method and save result if successful
	 * _ADR is not always present
	 */
	status = acpi_ut_evaluate_numeric_object (METHOD_NAME__ADR,
			  node, &address);

	if (ACPI_SUCCESS (status)) {
		info->address = address;
		info->valid |= ACPI_VALID_ADR;
	}

	return (AE_OK);
}