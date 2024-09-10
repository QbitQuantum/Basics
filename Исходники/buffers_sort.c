// Sort selected entries to the top of the list
void buffer_sort_selected(DirBuffer *buffer)
{
	struct MinList temp;
	DirEntry *entry,*first_file=0,*first_pos=0;

	// Lock buffer
	buffer_lock(buffer,TRUE);

	// Initialise temporary list
	NewList((struct List *)&temp);

	// Go through entries
	for (entry=(DirEntry *)buffer->entry_list.mlh_Head;
		entry->de_Node.dn_Succ;)
	{
		DirEntry *next=(DirEntry *)entry->de_Node.dn_Succ;

		// File?
		if (ENTRYTYPE(entry->de_Node.dn_Type)==ENTRY_FILE)
		{
			// Remove and add to temporary if selected
			if (entry->de_Flags&ENTF_SELECTED)
			{
				// Remember first position
				if (!first_pos) first_pos=(DirEntry *)entry->de_Node.dn_Pred;

				// Remove and re-add
				Remove((struct Node *)entry);
				AddTail((struct List *)&temp,(struct Node *)entry);
			}

			// Remember if the first file
			else
			if (!first_file) first_file=entry;
		}

		// Get next
		entry=next;
	}

	// Something in the temporary list?
	if (!(IsListEmpty((struct List *)&temp)))
	{
		// If we have a first file, get its predecessor
		if (first_file) first_pos=(DirEntry *)first_file->de_Node.dn_Pred;

		// Go through temporary list, add after first position
		for (entry=(DirEntry *)temp.mlh_Head;
			entry->de_Node.dn_Succ;)
		{
			DirEntry *next=(DirEntry *)entry->de_Node.dn_Succ;

			// Remove and add after last one
			Remove((struct Node *)entry);
			Insert((struct List *)&buffer->entry_list,(struct Node *)entry,(struct Node *)first_pos);

			// Bump next position
			first_pos=(DirEntry *)entry;

			// Get next
			entry=next;
		}
	}

	// Unlock buffer
	buffer_unlock(buffer);
}