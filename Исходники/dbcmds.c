void
acpi_db_set_method_data (
	NATIVE_CHAR             *type_arg,
	NATIVE_CHAR             *index_arg,
	NATIVE_CHAR             *value_arg)
{
	NATIVE_CHAR             type;
	u32                     index;
	u32                     value;
	acpi_walk_state         *walk_state;
	acpi_operand_object     *obj_desc;


	/* Validate Type_arg */

	STRUPR (type_arg);
	type = type_arg[0];
	if ((type != 'L') &&
		(type != 'A')) {
		acpi_os_printf ("Invalid SET operand: %s\n", type_arg);
		return;
	}

	/* Get the index and value */

	index = STRTOUL (index_arg, NULL, 16);
	value = STRTOUL (value_arg, NULL, 16);

	walk_state = acpi_ds_get_current_walk_state (acpi_gbl_current_walk_list);
	if (!walk_state) {
		acpi_os_printf ("There is no method currently executing\n");
		return;
	}


	/* Create and initialize the new object */

	obj_desc = acpi_ut_create_internal_object (ACPI_TYPE_INTEGER);
	if (!obj_desc) {
		acpi_os_printf ("Could not create an internal object\n");
		return;
	}

	obj_desc->integer.value = value;


	/* Store the new object into the target */

	switch (type) {
	case 'A':

		/* Set a method argument */

		if (index > MTH_NUM_ARGS) {
			acpi_os_printf ("Arg%d - Invalid argument name\n", index);
			return;
		}

		acpi_ds_store_object_to_local (AML_ARG_OP, index, obj_desc, walk_state);
		obj_desc = walk_state->arguments[index].object;

		acpi_os_printf ("Arg%d: ", index);
		acpi_db_display_internal_object (obj_desc, walk_state);
		break;

	case 'L':

		/* Set a method local */

		if (index > MTH_NUM_LOCALS) {
			acpi_os_printf ("Local%d - Invalid local variable name\n", index);
			return;
		}

		acpi_ds_store_object_to_local (AML_LOCAL_OP, index, obj_desc, walk_state);
		obj_desc = walk_state->local_variables[index].object;

		acpi_os_printf ("Local%d: ", index);
		acpi_db_display_internal_object (obj_desc, walk_state);
		break;

	default:
		break;
	}
}