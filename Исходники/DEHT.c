static void DEHT_freeResources(DEHT * ht, bool_t removeFiles)
{
	TRACE_FUNC_ENTRY();

	CHECK (NULL != ht);

	(void) fflush(ht->keyFP);
	FCLOSE(ht->keyFP);
	(void) fflush(ht->dataFP);
	FCLOSE(ht->dataFP);

	/* free ht cache if present */
	FREE(ht->hashTableOfPointersImageInMemory);
	FREE(ht->hashPointersForLastBlockImageInMemory);
	FREE(ht->userBuf);

	if (removeFiles) {
		/* attempt to remove bad files. Errors are silenced */
		CHECK(DEHT_removeFilesInternal(ht));
	}

	/* finally, free the ht itself */
	FREE(ht);

	goto LBL_CLEANUP;

LBL_ERROR:
	/* do nothing special - just quit */
	TRACE_FUNC_ERROR();

LBL_CLEANUP:
	/* bye */
	TRACE_FUNC_EXIT();
	return;
}