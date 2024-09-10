/*
 * Operating system primitives to support Windows shared memory.
 *
 * Windows shared memory implementation is done using file mapping
 * which can be backed by either physical file or system paging file.
 * Current implementation uses system paging file as other effects
 * like performance are not clear for physical file and it is used in similar
 * way for main shared memory in windows.
 *
 * A memory mapping object is a kernel object - they always get deleted when
 * the last reference to them goes away, either explicitly via a CloseHandle or
 * when the process containing the reference exits.
 */
static bool
dsm_impl_windows(dsm_op op, dsm_handle handle, Size request_size,
				 void **impl_private, void **mapped_address,
				 Size *mapped_size, int elevel)
{
	char	   *address;
	HANDLE		hmap;
	char		name[64];
	MEMORY_BASIC_INFORMATION info;

	/* Resize is not supported for Windows shared memory. */
	if (op == DSM_OP_RESIZE)
	{
		elog(elevel, "Windows shared memory segments cannot be resized");
		return false;
	}

	/* Since resize isn't supported, reattach is a no-op. */
	if (op == DSM_OP_ATTACH && *mapped_address != NULL)
		return true;

	/*
	 * Storing the shared memory segment in the Global\ namespace, can allow
	 * any process running in any session to access that file mapping object
	 * provided that the caller has the required access rights. But to avoid
	 * issues faced in main shared memory, we are using the naming convention
	 * similar to main shared memory. We can change here once issue mentioned
	 * in GetSharedMemName is resolved.
	 */
	snprintf(name, 64, "%s.%u", SEGMENT_NAME_PREFIX, handle);

	/*
	 * Handle teardown cases.  Since Windows automatically destroys the object
	 * when no references reamin, we can treat it the same as detach.
	 */
	if (op == DSM_OP_DETACH || op == DSM_OP_DESTROY)
	{
		if (*mapped_address != NULL
			&& UnmapViewOfFile(*mapped_address) == 0)
		{
			_dosmaperr(GetLastError());
			ereport(elevel,
					(errcode_for_dynamic_shared_memory(),
				   errmsg("could not unmap shared memory segment \"%s\": %m",
						  name)));
			return false;
		}
		if (*impl_private != NULL
			&& CloseHandle(*impl_private) == 0)
		{
			_dosmaperr(GetLastError());
			ereport(elevel,
					(errcode_for_dynamic_shared_memory(),
				  errmsg("could not remove shared memory segment \"%s\": %m",
						 name)));
			return false;
		}

		*impl_private = NULL;
		*mapped_address = NULL;
		*mapped_size = 0;
		return true;
	}

	/* Create new segment or open an existing one for attach. */
	if (op == DSM_OP_CREATE)
	{
		DWORD		size_high;
		DWORD		size_low;

		/* Shifts >= the width of the type are undefined. */
#ifdef _WIN64
		size_high = request_size >> 32;
#else
		size_high = 0;
#endif
		size_low = (DWORD) request_size;

		hmap = CreateFileMapping(INVALID_HANDLE_VALUE,	/* Use the pagefile */
								 NULL,	/* Default security attrs */
								 PAGE_READWRITE,		/* Memory is read/write */
								 size_high,		/* Upper 32 bits of size */
								 size_low,		/* Lower 32 bits of size */
								 name);
		if (!hmap)
		{
			_dosmaperr(GetLastError());
			ereport(elevel,
					(errcode_for_dynamic_shared_memory(),
				  errmsg("could not create shared memory segment \"%s\": %m",
						 name)));
			return false;
		}
		_dosmaperr(GetLastError());
		if (errno == EEXIST)
		{
			/*
			 * On Windows, when the segment already exists, a handle for the
			 * existing segment is returned.  We must close it before
			 * returning.  We don't do _dosmaperr here, so errno won't be
			 * modified.
			 */
			CloseHandle(hmap);
			return false;
		}
	}