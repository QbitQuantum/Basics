status_t
BDaemonClient::CreateTransaction(BPackageInstallationLocation location,
	BActivationTransaction& _transaction, BDirectory& _transactionDirectory)
{
	// get an info for the location
	BInstallationLocationInfo info;
	status_t error = GetInstallationLocationInfo(location, info);
	if (error != B_OK)
		return error;

	// open admin directory
	entry_ref entryRef;
	entryRef.device = info.PackagesDirectoryRef().device;
	entryRef.directory = info.PackagesDirectoryRef().node;
	error = entryRef.set_name(PACKAGES_DIRECTORY_ADMIN_DIRECTORY);
	if (error != B_OK)
		return error;
	
	BDirectory adminDirectory;
	error = adminDirectory.SetTo(&entryRef);
	if (error != B_OK)
		return error;

	// create a transaction directory
	int uniqueId = 1;
	BString directoryName;
	for (;; uniqueId++) {
		directoryName.SetToFormat("transaction-%d", uniqueId);
		if (directoryName.IsEmpty())
			return B_NO_MEMORY;

		error = adminDirectory.CreateDirectory(directoryName,
			&_transactionDirectory);
		if (error == B_OK)
			break;
		if (error != B_FILE_EXISTS)
			return error;
	}

	// init the transaction
	error = _transaction.SetTo(location, info.ChangeCount(), directoryName);
	if (error != B_OK) {
		BEntry entry;
		_transactionDirectory.GetEntry(&entry);
		_transactionDirectory.Unset();
		if (entry.InitCheck() == B_OK)
			entry.Remove();
		return error;
	}

	return B_OK;
}