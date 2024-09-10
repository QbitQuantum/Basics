static bool _BEDecode_list(void *aiData, size_t aiLength, BEType *aoType, BEList **aoList, size_t *aoUsedLength)
{
	// List, e.g. l4:spam4:eggse

	// Create list
	BEList *list = malloc(sizeof (BEList));
	if(!list)
		return NULL;
	list->entries = NULL;
	list->size = 0;

	// Initialize
	COInitialize(list);
	COSetDestructor(list, &_BEListDelete);

	// Look for list items
	size_t currentStart = 1;
	while(((char *)aiData)[currentStart] != 'e')
	{
		BEType subType;

		BEString     *subString     = NULL;
		int          subInteger;
		BEList       *subList       = NULL;
		BEDictionary *subDictionary = NULL;

		size_t subUsedLength;

		// Decode one sub-item
		bool success = BEDecode(
			aiData+currentStart, aiLength-currentStart-1,
			&subType,
			&subString, &subInteger, &subList, &subDictionary,
			&subUsedLength
		);

		// Check for errors
		if(!success)
		{
			// Cleanup
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(list);

			return false;
		}

		// Expand list
		// FIXME optimize by getting rid of realloc
		struct _BEListEntry *entries = realloc(list->entries, (list->size+1)*sizeof (struct _BEListEntry));
		if(!entries)
		{
			// Cleanup
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(list);

			return false;
		}
		list->entries = entries;
		list->size++;

		// Fill list
		switch(subType)
		{
			case BE_STRING:
				list->entries[list->size-1].type = BE_STRING;
				list->entries[list->size-1].data.string = subString;
				break;

			case BE_INTEGER:
				list->entries[list->size-1].type = BE_INTEGER;
				list->entries[list->size-1].data.integer = subInteger;
				break;

			case BE_LIST:
				list->entries[list->size-1].type = BE_LIST;
				list->entries[list->size-1].data.list = subList;
				break;

			case BE_DICTIONARY:
				list->entries[list->size-1].type = BE_DICTIONARY;
				list->entries[list->size-1].data.dictionary = subDictionary;
				break;
		}

		// Move to next
		currentStart += subUsedLength;
	}

	// Set result
	*aoType = BE_LIST;
	*aoList = list;
	if(aoUsedLength)
		*aoUsedLength = currentStart+1;
	return true;
}