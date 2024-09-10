BOOL xf_keyboard_action_script_init(xfContext* xfc)
{
	FILE* keyScript;
	char* keyCombination;
	char buffer[1024] = { 0 };
	char command[1024] = { 0 };

	if (xfc->actionScript)
	{
		free(xfc->actionScript);
		xfc->actionScript = NULL;
	}

	if (PathFileExistsA("/usr/share/freerdp/action.sh"))
		xfc->actionScript = _strdup("/usr/share/freerdp/action.sh");

	if (!xfc->actionScript)
		return FALSE;

	xfc->keyCombinations = ArrayList_New(TRUE);
	if (!xfc->keyCombinations)
		return FALSE;

	ArrayList_Object(xfc->keyCombinations)->fnObjectFree = free;

	sprintf_s(command, sizeof(command), "%s key", xfc->actionScript);

	keyScript = popen(command, "r");

	if (!keyScript)
	{
		free(xfc->actionScript);
		xfc->actionScript = NULL;
		return FALSE;
	}

	while (fgets(buffer, sizeof(buffer), keyScript) != NULL)
	{
		strtok(buffer, "\n");
		keyCombination = _strdup(buffer);
		if (!keyCombination || ArrayList_Add(xfc->keyCombinations, keyCombination) < 0)
		{
			ArrayList_Free(xfc->keyCombinations);
			free(xfc->actionScript);
			xfc->actionScript = NULL;
			pclose(keyScript);
			return FALSE;
		}
	}

	pclose(keyScript);
	return xf_event_action_script_init(xfc);

}