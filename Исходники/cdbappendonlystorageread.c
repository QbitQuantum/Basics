/*
 * Initialize AppendOnlyStorageRead.
 *
 * The AppendOnlyStorageRead data structure is initialized
 * once for a read "session" and can be used to read
 * Append-Only Storage Blocks from 1 or more segment files.
 *
 * The current file to read to is opened with the
 * AppendOnlyStorageRead_OpenFile routine.
 */
void AppendOnlyStorageRead_Init(
	AppendOnlyStorageRead			*storageRead,
				/* The data structure to initialize. */

	MemoryContext 					memoryContext,
				/*
				 * The memory context to use for buffers and
				 * other memory needs.  When NULL, the
				 * current memory context is used.
				 */
    int32                			maxBufferLen,
				/*
				 * The maximum Append-Only Storage Block
				 * length including all storage headers.
				 */
	char							*relationName,
				/*
				 * Name of the relation to use in system
				 * logging and error messages.
				 */

	char							*title,
				/*
				 * A phrase that better describes the purpose of the this open.
				 *
				 * The caller manages the storage for this.
				 */

	AppendOnlyStorageAttributes		*storageAttributes)
				/*
				 * The Append-Only Storage Attributes
				 * from relation creation.
				 */
{
	int		relationNameLen;
	uint8	*memory;
	int32	memoryLen;
	MemoryContext	oldMemoryContext;

	Assert(storageRead != NULL);

	// UNDONE: Range check maxBufferLen

	Assert(relationName != NULL);
	Assert(storageAttributes != NULL);

	// UNDONE: Range check fields in storageAttributes

	MemSet(storageRead, 0, sizeof(AppendOnlyStorageRead));

	storageRead->maxBufferLen = maxBufferLen;

	if (memoryContext == NULL)
		storageRead->memoryContext = CurrentMemoryContext;
	else
		storageRead->memoryContext = memoryContext;

	oldMemoryContext = MemoryContextSwitchTo(storageRead->memoryContext);

	memcpy(
		&storageRead->storageAttributes,
		storageAttributes,
		sizeof(AppendOnlyStorageAttributes));

	relationNameLen = strlen(relationName);
	storageRead->relationName = (char *) palloc(relationNameLen + 1);
	memcpy(storageRead->relationName, relationName, relationNameLen + 1);

	storageRead->title = title;

	storageRead->minimumHeaderLen =
		AppendOnlyStorageFormat_RegularHeaderLenNeeded(
									storageRead->storageAttributes.checksum);

	/*
	 * Initialize BufferedRead.
	 */
	storageRead->largeReadLen = 2 * storageRead->maxBufferLen;

	memoryLen =
		BufferedReadMemoryLen(
					storageRead->maxBufferLen,
					storageRead->largeReadLen);

	Assert(CurrentMemoryContext == storageRead->memoryContext);
	memory = (uint8*)palloc(memoryLen);

	BufferedReadInit(&storageRead->bufferedRead,
					 memory,
					 memoryLen,
					 storageRead->maxBufferLen,
					 storageRead->largeReadLen,
					 relationName);

	elogif(Debug_appendonly_print_scan || Debug_appendonly_print_read_block, LOG,
		"Append-Only Storage Read initialize for table '%s' "
		     "(compression = %s, compression level %d, maximum buffer length %d, large read length %d)",
		     storageRead->relationName,
		     (storageRead->storageAttributes.compress ? "true" : "false"),
		     storageRead->storageAttributes.compressLevel,
		     storageRead->maxBufferLen,
		     storageRead->largeReadLen);

	storageRead->file = -1;

	MemoryContextSwitchTo(oldMemoryContext);

	storageRead->isActive = true;

}