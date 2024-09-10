void
acpi_db_prep_namestring (
	NATIVE_CHAR             *name)
{


	if (!name) {
		return;
	}

	STRUPR (name);

	/* Convert a leading forward slash to a backslash */

	if (*name == '/') {
		*name = '\\';
	}

	/* Ignore a leading backslash, this is the root prefix */

	if (*name == '\\') {
		name++;
	}

	/* Convert all slash path separators to dots */

	while (*name) {
		if ((*name == '/') ||
			(*name == '\\')) {
			*name = '.';
		}

		name++;
	}
}