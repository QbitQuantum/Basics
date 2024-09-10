/*! \brief Reads through the database and builds a complete set of installed types lists.

	An initial set of cached messages are also created.
*/
status_t
InstalledTypes::_BuildInstalledTypesList()
{
	status_t err = B_OK;
	_Unset();

	// Create empty "cached messages" so proper messages
	// will be built up as we add new types
	try {
		fCachedMessage = new BMessage();
		fCachedSupertypesMessage = new BMessage();
	} catch (std::bad_alloc) {
		err = B_NO_MEMORY;
	}

	BDirectory root;
	if (!err)
		err = root.SetTo(get_database_directory().c_str());
	if (!err) {
		root.Rewind();
		while (true) {
			BEntry entry;
			err = root.GetNextEntry(&entry);
			if (err) {
				// If we've come to the end of list, it's not an error
				if (err == B_ENTRY_NOT_FOUND)
					err = B_OK;
				break;
			} else {
				// Check that this entry is both a directory and a valid MIME string
				char supertype[B_PATH_NAME_LENGTH];
				if (entry.IsDirectory()
				      && entry.GetName(supertype) == B_OK
				         && BMimeType::IsValid(supertype))
				{
					// Make sure our string is all lowercase
					BPrivate::Storage::to_lower(supertype);

					// Add this supertype
					std::map<std::string, Supertype>::iterator i;
					if (_AddSupertype(supertype, i) != B_OK)
						DBG(OUT("Mime::InstalledTypes::BuildInstalledTypesList() -- Error adding supertype '%s': 0x%lx\n",
							supertype, err));
					Supertype &supertypeRef = fSupertypes[supertype];

					// Now iterate through this supertype directory and add
					// all of its subtypes
					BDirectory dir;
					if (dir.SetTo(&entry) == B_OK) {
						dir.Rewind();
						while (true) {
							BEntry subEntry;
							err = dir.GetNextEntry(&subEntry);
							if (err) {
								// If we've come to the end of list, it's not an error
								if (err == B_ENTRY_NOT_FOUND)
									err = B_OK;
								break;
							} else {
								// We need to preserve the case of the type name for
								// queries, so we can't use the file name directly
								BString type;
								int32 subStart;
								BNode node(&subEntry);
								if (node.InitCheck() == B_OK
									&& node.ReadAttrString(kTypeAttr, &type) >= B_OK
									&& (subStart = type.FindFirst('/')) > 0) {
									// Add the subtype
									if (_AddSubtype(supertypeRef, type.String()
											+ subStart + 1) != B_OK) {
										DBG(OUT("Mime::InstalledTypes::BuildInstalledTypesList() -- Error adding subtype '%s/%s': 0x%lx\n",
											supertype, type.String() + subStart + 1, err));
									}
								}
							}
						}
					} else {
						DBG(OUT("Mime::InstalledTypes::BuildInstalledTypesList(): "
						          "Failed opening supertype directory '%s'\n",
						            supertype));
					}
				}
			}
		}
	} else {
		DBG(OUT("Mime::InstalledTypes::BuildInstalledTypesList(): "
		          "Failed opening mime database directory '%s'\n",
		            get_database_directory().c_str()));
	}
	fHaveDoneFullBuild = true;
	return err;

}