ACPI_STATUS
acpi_ns_root_initialize (void)
{
	ACPI_STATUS             status = AE_OK;
	PREDEFINED_NAMES        *init_val = NULL;
	ACPI_NAMESPACE_NODE     *new_node;
	ACPI_OPERAND_OBJECT     *obj_desc;


	acpi_cm_acquire_mutex (ACPI_MTX_NAMESPACE);

	/*
	 * The global root ptr is initially NULL, so a non-NULL value indicates
	 * that Acpi_ns_root_initialize() has already been called; just return.
	 */

	if (acpi_gbl_root_node) {
		status = AE_OK;
		goto unlock_and_exit;
	}


	/*
	 * Tell the rest of the subsystem that the root is initialized
	 * (This is OK because the namespace is locked)
	 */

	acpi_gbl_root_node = &acpi_gbl_root_node_struct;


	/* Enter the pre-defined names in the name table */

	for (init_val = acpi_gbl_pre_defined_names; init_val->name; init_val++) {
		status = acpi_ns_lookup (NULL, init_val->name,
				 (OBJECT_TYPE_INTERNAL) init_val->type,
				 IMODE_LOAD_PASS2, NS_NO_UPSEARCH,
				 NULL, &new_node);


		/*
		 * Name entered successfully.
		 * If entry in Pre_defined_names[] specifies an
		 * initial value, create the initial value.
		 */

		if (init_val->val) {
			/*
			 * Entry requests an initial value, allocate a
			 * descriptor for it.
			 */

			obj_desc = acpi_cm_create_internal_object (
					  (OBJECT_TYPE_INTERNAL) init_val->type);

			if (!obj_desc) {
				status = AE_NO_MEMORY;
				goto unlock_and_exit;
			}

			/*
			 * Convert value string from table entry to
			 * internal representation. Only types actually
			 * used for initial values are implemented here.
			 */

			switch (init_val->type)
			{

			case ACPI_TYPE_NUMBER:

				obj_desc->number.value =
						(ACPI_INTEGER) STRTOUL (init_val->val, NULL, 10);
				break;


			case ACPI_TYPE_STRING:

				obj_desc->string.length =
						(u16) STRLEN (init_val->val);

				/*
				 * Allocate a buffer for the string.  All
				 * String.Pointers must be allocated buffers!
				 * (makes deletion simpler)
				 */
				obj_desc->string.pointer = acpi_cm_allocate (
						   (obj_desc->string.length + 1));
				if (!obj_desc->string.pointer) {
					acpi_cm_remove_reference (obj_desc);
					status = AE_NO_MEMORY;
					goto unlock_and_exit;
				}

				STRCPY (obj_desc->string.pointer, init_val->val);
				break;


			case ACPI_TYPE_MUTEX:

				obj_desc->mutex.sync_level =
						(u16) STRTOUL (init_val->val, NULL, 10);

				if (STRCMP (init_val->name, "_GL_") == 0) {
					/*
					 * Create a counting semaphore for the
					 * global lock
					 */
					status = acpi_os_create_semaphore (ACPI_NO_UNIT_LIMIT,
							 1, &obj_desc->mutex.semaphore);

					if (ACPI_FAILURE (status)) {
						goto unlock_and_exit;
					}
					/*
					 * We just created the mutex for the
					 * global lock, save it
					 */

					acpi_gbl_global_lock_semaphore = obj_desc->mutex.semaphore;
				}

				else {
					/* Create a mutex */

					status = acpi_os_create_semaphore (1, 1,
							   &obj_desc->mutex.semaphore);

					if (ACPI_FAILURE (status)) {
						goto unlock_and_exit;
					}
				}
				break;


			default:
				REPORT_ERROR (("Unsupported initial type value %X\n",
					init_val->type));
				acpi_cm_remove_reference (obj_desc);
				obj_desc = NULL;
				continue;
			}

			/* Store pointer to value descriptor in the Node */

			acpi_ns_attach_object (new_node, obj_desc,
					   obj_desc->common.type);
		}
	}


unlock_and_exit:
	acpi_cm_release_mutex (ACPI_MTX_NAMESPACE);
	return (status);
}