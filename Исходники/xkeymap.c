static void
add_sequence(char *rest, char *mapname)
{
	KeySym keysym;
	key_translation *tr, **prev_next;
	size_t chars;
	char keyname[KEYMAP_MAX_LINE_LENGTH];

	/* Skip over whitespace after the sequence keyword */
	chars = strspn(rest, " \t");
	rest += chars;

	/* Fetch the keysym name */
	chars = strcspn(rest, " \t\0");
	STRNCPY(keyname, rest, chars + 1);
	rest += chars;

	keysym = XStringToKeysym(keyname);
	if (keysym == NoSymbol)
	{
		DEBUG_KBD(("Bad keysym \"%s\" in keymap %s (ignoring line)\n", keyname, mapname));
		return;
	}


	DEBUG_KBD(("Adding sequence for keysym (0x%lx, %s) -> ", keysym, keyname));

	free_key_translation(keymap[keysym & KEYMAP_MASK]);
	prev_next = &keymap[keysym & KEYMAP_MASK];

	while (*rest)
	{
		/* Skip whitespace */
		chars = strspn(rest, " \t");
		rest += chars;

		/* Fetch the keysym name */
		chars = strcspn(rest, " \t\0");
		STRNCPY(keyname, rest, chars + 1);
		rest += chars;

		keysym = XStringToKeysym(keyname);
		if (keysym == NoSymbol)
		{
			DEBUG_KBD(("Bad keysym \"%s\" in keymap %s (ignoring line)\n", keyname,
				   mapname));
			return;
		}

		/* Allocate space for key_translation structure */
		tr = (key_translation *) xmalloc(sizeof(key_translation));
		memset(tr, 0, sizeof(key_translation));
		*prev_next = tr;
		prev_next = &tr->next;
		tr->seq_keysym = keysym;

		DEBUG_KBD(("0x%x, ", (unsigned int) keysym));
	}
	DEBUG_KBD(("\n"));
}