acpi_status
acpi_ns_build_internal_name (
	acpi_namestring_info    *info)
{
	u32                     num_segments = info->num_segments;
	NATIVE_CHAR             *internal_name = info->internal_name;
	NATIVE_CHAR             *external_name = info->next_external_char;
	NATIVE_CHAR             *result = NULL;
	u32                     i;


	FUNCTION_TRACE ("Ns_build_internal_name");


	/* Setup the correct prefixes, counts, and pointers */

	if (info->fully_qualified) {
		internal_name[0] = '\\';

		if (num_segments <= 1) {
			result = &internal_name[1];
		}
		else if (num_segments == 2) {
			internal_name[1] = AML_DUAL_NAME_PREFIX;
			result = &internal_name[2];
		}
		else {
			internal_name[1] = AML_MULTI_NAME_PREFIX_OP;
			internal_name[2] = (char) num_segments;
			result = &internal_name[3];
		}
	}

	else {
		/*
		 * Not fully qualified.
		 * Handle Carats first, then append the name segments
		 */
		i = 0;
		if (info->num_carats) {
			for (i = 0; i < info->num_carats; i++) {
				internal_name[i] = '^';
			}
		}

		if (num_segments == 1) {
			result = &internal_name[i];
		}

		else if (num_segments == 2) {
			internal_name[i] = AML_DUAL_NAME_PREFIX;
			result = &internal_name[i+1];
		}

		else {
			internal_name[i] = AML_MULTI_NAME_PREFIX_OP;
			internal_name[i+1] = (char) num_segments;
			result = &internal_name[i+2];
		}
	}


	/* Build the name (minus path separators) */

	for (; num_segments; num_segments--) {
		for (i = 0; i < ACPI_NAME_SIZE; i++) {
			if (acpi_ns_valid_path_separator (*external_name) ||
			   (*external_name == 0)) {
				/* Pad the segment with underscore(s) if segment is short */

				result[i] = '_';
			}

			else {
				/* Convert the character to uppercase and save it */

				result[i] = (char) TOUPPER (*external_name);
				external_name++;
			}
		}

		/* Now we must have a path separator, or the pathname is bad */

		if (!acpi_ns_valid_path_separator (*external_name) &&
			(*external_name != 0)) {
			return_ACPI_STATUS (AE_BAD_PARAMETER);
		}

		/* Move on the next segment */

		external_name++;
		result += ACPI_NAME_SIZE;
	}


	/* Terminate the string */

	*result = 0;

	if (info->fully_qualified) {
		ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "returning [%p] (abs) \"\\%s\"\n",
			internal_name, &internal_name[0]));
	}
	else {
		ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "returning [%p] (rel) \"%s\"\n",
			internal_name, &internal_name[2]));
	}

	return_ACPI_STATUS (AE_OK);
}