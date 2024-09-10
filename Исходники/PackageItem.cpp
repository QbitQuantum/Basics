status_t
PackageLink::WriteToPath(const char *path, ItemState *state)
{
	if (state == NULL)
		return B_ERROR;

	status_t ret = B_OK;
	BSymLink symlink;
	parser_debug("Symlink: %s WriteToPath() called!\n", fPath.String());

	BPath &destination = state->destination;
	BDirectory *dir = &state->parent;

	if (state->status == B_NO_INIT || destination.InitCheck() != B_OK
		|| dir->InitCheck() != B_OK) {
		// Not yet initialized
		ret = InitPath(path, &destination);
		if (ret != B_OK)
			return ret;

		BString linkName(destination.Leaf());
		parser_debug("%s:%s:%s\n", fPath.String(), destination.Path(),
			linkName.String());

		BPath dirPath;
		ret = destination.GetParent(&dirPath);
		ret = dir->SetTo(dirPath.Path());

		if (ret == B_ENTRY_NOT_FOUND) {
			ret = create_directory(dirPath.Path(), kDefaultMode);
			if (ret != B_OK) {
				parser_debug("create_directory()) failed\n");
				return B_ERROR;
			}
		}
		if (ret != B_OK) {
			parser_debug("destination InitCheck failed %s for %s\n",
				strerror(ret), dirPath.Path());
			return ret;
		}

		ret = dir->CreateSymLink(destination.Path(), fLink.String(), &symlink);
		if (ret == B_FILE_EXISTS) {
			// We need to check if the existing symlink is pointing at the same path
			// as our new one - if not, let's prompt the user
			symlink.SetTo(destination.Path());
			BPath oldLink;

			ret = symlink.MakeLinkedPath(dir, &oldLink);
			chdir(dirPath.Path());

			if (ret == B_BAD_VALUE || oldLink != fLink.String())
				state->status = ret = B_FILE_EXISTS;
			else
				ret = B_OK;
		}
	}

	if (state->status == B_FILE_EXISTS) {
		switch (state->policy) {
			case P_EXISTS_OVERWRITE:
			{
				BEntry entry;
				ret = entry.SetTo(destination.Path());
				if (ret != B_OK)
					return ret;

				entry.Remove();
				ret = dir->CreateSymLink(destination.Path(), fLink.String(),
					&symlink);
				break;
			}

			case P_EXISTS_NONE:
			case P_EXISTS_ASK:
				ret = B_FILE_EXISTS;
				break;

			case P_EXISTS_SKIP:
				return B_OK;
		}
	}

	if (ret != B_OK) {
		parser_debug("CreateSymLink failed\n");
		return ret;
	}

	parser_debug(" Symlink created!\n");

	ret = symlink.SetPermissions(static_cast<mode_t>(fMode));

	if (fCreationTime && ret == B_OK)
		ret = symlink.SetCreationTime(static_cast<time_t>(fCreationTime));

	if (fModificationTime && ret == B_OK) {
		ret = symlink.SetModificationTime(static_cast<time_t>(
			fModificationTime));
	}

	if (ret != B_OK) {
		parser_debug("Failed to set symlink attributes\n");
		return ret;
	}

	if (fOffset) {
		// Symlinks also seem to have attributes - so parse them
		ret = HandleAttributes(&destination, &symlink, "LnDa");
	}

	return ret;
}