static LONG MSGRemoveContext(SCARDCONTEXT hContext, SCONTEXT * threadContext)
{
	LONG rv;
	int lrv;

	if (threadContext->hContext != hContext)
		return SCARD_E_INVALID_VALUE;

	(void)pthread_mutex_lock(&threadContext->cardsList_lock);
	while (list_size(&threadContext->cardsList) != 0)
	{
		READER_CONTEXT * rContext = NULL;
		SCARDHANDLE hCard, hLockId;
		void *ptr;

		/*
		 * Disconnect each of these just in case
		 */
		ptr = list_get_at(&threadContext->cardsList, 0);
		if (NULL == ptr)
		{
			Log1(PCSC_LOG_CRITICAL, "list_get_at failed");
			continue;
		}
		hCard = *(int32_t *)ptr;

		/*
		 * Unlock the sharing
		 */
		rv = RFReaderInfoById(hCard, &rContext);
		if (rv != SCARD_S_SUCCESS)
		{
			(void)pthread_mutex_unlock(&threadContext->cardsList_lock);
			return rv;
		}

		hLockId = rContext->hLockId;
		rContext->hLockId = 0;

		if (hCard != hLockId)
		{
			/*
			 * if the card is locked by someone else we do not reset it
			 * and simulate a card removal
			 */
			rv = SCARD_W_REMOVED_CARD;
		}
		else
		{
			/*
			 * We will use SCardStatus to see if the card has been
			 * reset there is no need to reset each time
			 * Disconnect is called
			 */
			rv = SCardStatus(hCard, NULL, NULL, NULL, NULL, NULL, NULL);
		}

		if (rv == SCARD_W_RESET_CARD || rv == SCARD_W_REMOVED_CARD)
			(void)SCardDisconnect(hCard, SCARD_LEAVE_CARD);
		else
			(void)SCardDisconnect(hCard, SCARD_RESET_CARD);

		/* Remove entry from the list */
		lrv = list_delete_at(&threadContext->cardsList, 0);
		if (lrv < 0)
			Log2(PCSC_LOG_CRITICAL,
				"list_delete_at failed with return value: %d", lrv);

		UNREF_READER(rContext)
	}
	(void)pthread_mutex_unlock(&threadContext->cardsList_lock);
	list_destroy(&threadContext->cardsList);

	/* We only mark the context as no longer in use.
	 * The memory is freed in MSGCleanupCLient() */
	threadContext->hContext = 0;

	return SCARD_S_SUCCESS;
}