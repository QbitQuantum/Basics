status_t
Inode::LoadAttrDirHandle()
{
	if (fInfo.fAttrDir.fSize != 0)
		return B_OK;

	FileHandle handle;
	status_t result;

	if (fFileSystem->NamedAttrs()) {
		result = NFS4Inode::OpenAttrDir(&handle);
		if (result == B_OK) {
			fInfo.fAttrDir = handle;
			return B_OK;
		}

		if (result != B_UNSUPPORTED)
			return result;

		fFileSystem->SetNamedAttrs(false);
	}

	if (!fFileSystem->GetConfiguration().fEmulateNamedAttrs)
		return B_UNSUPPORTED;

	char* attrDir
		= reinterpret_cast<char*>(malloc(strlen(Name()) + 32));
	if (attrDir == NULL)
		return B_NO_MEMORY;
	strcpy(attrDir, ".");
	strcat(attrDir, Name());
	strcat(attrDir, "-haiku-attrs");

	result = NFS4Inode::LookUp(attrDir, NULL, NULL, &handle, true);
	if (result == B_ENTRY_NOT_FOUND) {
		ChangeInfo change;
		struct stat st;
		Stat(&st);
		st.st_mode |= S_IXUSR | S_IXGRP | S_IXOTH;
		result = NFS4Inode::CreateObject(attrDir, NULL, st.st_mode, NF4DIR,
			&change, NULL, &handle, true);
	}

	free(attrDir);

	if (result != B_OK)
		return result;

	fInfo.fAttrDir = handle;
	return B_OK;
}