void DisablePlugins()
{
	char buffer[10000];

	if ( GetSettings("DisablePlugins", buffer, sizeof(buffer)) ) {
		char *name;
		char *value;

		name = buffer;
		while(name[0] != '\0') {
			value = strchr(name, '=');
			if (value == NULL)
				value = &name[mir_strlen(name)];

			// Has " ?
			if (*name == '"' && *(value-1) == '"') {
				name++;
				*(value-1) = '\0';
			}

			// Disable it
			if (name[0] != '\0') {
				CharLowerA(name);
				if (db_get_b(NULL, PLUGINDISABLELIST, name, 0) != 1)
				{
					db_set_b(NULL, PLUGINDISABLELIST, name, 1);
				}
			}

			// Get next one
			name = value + mir_strlen(value) + 1;
		}
	}
}