ERRORCODE FileListRecord::do_find_file(LPCSTR name, DB_RECORD_NUMBER far *lprecord, FILE_SEARCH_KEY *key)
{
#if 0
	od("Dump: ");
	for (int i = 0; i < m_file_array.count(); i++)
	{
		FILE_ARRAY_ELEMENT_PTR elem = m_file_array.get_file(i);
		od("(h:%x, r:%ld)", elem->hash, elem->record_number);
	}
	od("\r\n");
#endif
/*
// We want to perform a binary search on the array.
// The search key will be the hash value.
*/

	key->this_record = this;
	key->search_name = name;
	key->search_hash = hash_name(name);
	key->last_searched_element = NULL;

//	od("Look for file name '%s' (hash: %x)\r\n", name, key->search_hash);

	SHORT count;

	if ((count = m_file_array.count()) != 0)
	{
	/*
	// Get the first entry.
	// All entries in the array have the same selector.
	*/
		FILE_ARRAY_ELEMENT_PTR elem = m_file_array.get_file(0);

	/* Do the search. */

		void *ret = bsearch(key, elem, count,
								  sizeof(FILE_ARRAY_ELEMENT),
								  file_element_compare);

	/* Did we find it? */

		if (ret != NULL)
		{
			if (key->last_result != 0)
			{
			/* This is actually an error. */
				return (ERRORCODE)key->last_result;
			}

		/* Found it! */

			elem = (FILE_ARRAY_ELEMENT_PTR)ret;

		/* Update our time stamp. */

			elem->last_access = (DWORD)time(NULL);

			if (lprecord != NULL)
			{
				*lprecord = elem->record_number;
			}

			return ERRORCODE_None;
		}
	}

/* Not found. */

	return ERRORCODE_DoesNotExist;
}