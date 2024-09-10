status_t
Partition::Scan(bool mountFileSystems, bool isBootDevice)
{
	// scan for partitions first (recursively all eventual children as well)

	TRACE(("%p Partition::Scan()\n", this));

	// if we were not booted from the real boot device, we won't scan
	// the device we were booted from (which is likely to be a slow
	// floppy or CD)
	if (isBootDevice && gKernelArgs.boot_volume.GetBool(
			BOOT_VOLUME_BOOTED_FROM_IMAGE, false)) {
		return B_ENTRY_NOT_FOUND;
	}

	const partition_module_info *bestModule = NULL;
	void *bestCookie = NULL;
	float bestPriority = -1;

	for (int32 i = 0; i < sNumPartitionModules; i++) {
		const partition_module_info *module = sPartitionModules[i];
		void *cookie = NULL;
		NodeOpener opener(this, O_RDONLY);

		TRACE(("check for partitioning_system: %s\n", module->pretty_name));

		float priority
			= module->identify_partition(opener.Descriptor(), this, &cookie);
		if (priority < 0.0)
			continue;

		TRACE(("  priority: %ld\n", (int32)(priority * 1000)));
		if (priority <= bestPriority) {
			// the disk system recognized the partition worse than the currently
			// best one
			module->free_identify_partition_cookie(this, cookie);
			continue;
		}

		// a new winner, replace the previous one
		if (bestModule)
			bestModule->free_identify_partition_cookie(this, bestCookie);
		bestModule = module;
		bestCookie = cookie;
		bestPriority = priority;
	}

	// find the best FS module
	const file_system_module_info *bestFSModule = NULL;
	float bestFSPriority = -1;
	for (int32 i = 0; i < sNumFileSystemModules; i++) {
		if (sFileSystemModules[i]->identify_file_system == NULL)
			continue;

		float priority = sFileSystemModules[i]->identify_file_system(this);
		if (priority <= 0)
			continue;

		if (priority > bestFSPriority) {
			bestFSModule = sFileSystemModules[i];
			bestFSPriority = priority;
		}
	}

	// now let the best matching disk system scan the partition
	if (bestModule && bestPriority >= bestFSPriority) {
		NodeOpener opener(this, O_RDONLY);
		status_t status = bestModule->scan_partition(opener.Descriptor(), this,
			bestCookie);
		bestModule->free_identify_partition_cookie(this, bestCookie);

		if (status != B_OK) {
			dprintf("Partitioning module `%s' recognized the partition, but "
				"failed to scan it\n", bestModule->pretty_name);
			return status;
		}

		fIsPartitioningSystem = true;

		content_type = bestModule->pretty_name;
		flags |= B_PARTITION_PARTITIONING_SYSTEM;

		// now that we've found something, check our children
		// out as well!

		NodeIterator iterator = fChildren.GetIterator();
		Partition *child = NULL;

		while ((child = (Partition *)iterator.Next()) != NULL) {
			TRACE(("%p Partition::Scan(): scan child %p (start = %Ld, size "
				"= %Ld, parent = %p)!\n", this, child, child->offset,
				child->size, child->Parent()));

			child->Scan(mountFileSystems);

			if (!mountFileSystems || child->IsFileSystem()) {
				// move the partitions containing file systems to the partition
				// list
				fChildren.Remove(child);
				gPartitions.Add(child);
			}
		}

		// remove all unused children (we keep only file systems)

		while ((child = (Partition *)fChildren.Head()) != NULL) {
			fChildren.Remove(child);
			delete child;
		}

		// remember the name of the module that identified us
		fModuleName = bestModule->module.name;

		return B_OK;
	}

	// scan for file systems

	if (mountFileSystems) {
		// TODO: Use the FS module we've got, if any. Requires to implement the
		// identify_file_system() hook in every FS.
		return Mount();
	}

	return B_ENTRY_NOT_FOUND;
}