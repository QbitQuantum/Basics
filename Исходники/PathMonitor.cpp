status_t
PathHandler::_AddDirectory(BEntry& entry, bool notify)
{
	WatchedDirectory directory;
	status_t status = entry.GetNodeRef(&directory.node);
	if (status != B_OK)
		return status;

#ifdef TRACE_PATH_MONITOR
{
	BPath path(&entry);
	TRACE("  ADD DIRECTORY %s, %ld:%Ld\n",
		path.Path(), directory.node.device, directory.node.node);
}
#endif

	// check if we are already know this directory

	// TODO: It should be possible to ommit this check if we know it
	// can't be the case (for example when adding subfolders recursively,
	// although in that case, the API user may still have added this folder
	// independently, so for now, it should be the safest to perform this
	// check in all cases.)
	if (_HasDirectory(directory.node))
		return B_OK;

	directory.contained = _IsContained(entry);

	uint32 flags;
	if (directory.contained)
		flags = (fFlags & WATCH_NODE_FLAG_MASK) | B_WATCH_DIRECTORY;
	else
		flags = B_WATCH_DIRECTORY;

	status = watch_node(&directory.node, flags, this);
	if (status != B_OK)
		return status;

	fDirectories.insert(directory);

	if (_WatchRecursively()) {
		BDirectory dir(&directory.node);
		while (dir.GetNextEntry(&entry) == B_OK) {
			if (entry.IsDirectory()) {
				// and here is the recursion:
				if (_AddDirectory(entry, notify) != B_OK)
					break;
			} else if (!_WatchFoldersOnly()) {
				if (_AddFile(entry, notify) != B_OK)
					break;
			}
		}
	}

#if 0
	BEntry parent;
	if (entry.GetParent(&parent) == B_OK
		&& !_IsContained(parent)) {
		// TODO: remove parent from watched directories
	}
#endif
	return B_OK;
}