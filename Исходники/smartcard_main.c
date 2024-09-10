static void smartcard_init(DEVICE* device)
{
	int index;
	int keyCount;
	ULONG_PTR* pKeys;
	SCARDCONTEXT hContext;
	SMARTCARD_CONTEXT* pContext;
	SMARTCARD_DEVICE* smartcard = (SMARTCARD_DEVICE*) device;

	/**
	 * On protocol termination, the following actions are performed:
	 * For each context in rgSCardContextList, SCardCancel is called causing all outstanding messages to be processed.
	 * After there are no more outstanding messages, SCardReleaseContext is called on each context and the context MUST
	 * be removed from rgSCardContextList.
	 */

	/**
	 * Call SCardCancel on existing contexts, unblocking all outstanding IRPs.
	 */

	if (ListDictionary_Count(smartcard->rgSCardContextList) > 0)
	{
		pKeys = NULL;
		keyCount = ListDictionary_GetKeys(smartcard->rgSCardContextList, &pKeys);

		for (index = 0; index < keyCount; index++)
		{
			pContext = (SMARTCARD_CONTEXT*) ListDictionary_GetItemValue(smartcard->rgSCardContextList, (void*) pKeys[index]);

			if (!pContext)
				continue;

			hContext = pContext->hContext;

			if (SCardIsValidContext(hContext))
			{
				SCardCancel(hContext);
			}
		}

		free(pKeys);
	}

	/**
	 * Call SCardReleaseContext on remaining contexts and remove them from rgSCardContextList.
	 */

	if (ListDictionary_Count(smartcard->rgSCardContextList) > 0)
	{
		pKeys = NULL;
		keyCount = ListDictionary_GetKeys(smartcard->rgSCardContextList, &pKeys);

		for (index = 0; index < keyCount; index++)
		{
			pContext = (SMARTCARD_CONTEXT*) ListDictionary_Remove(smartcard->rgSCardContextList, (void*) pKeys[index]);

			if (!pContext)
				continue;

			hContext = pContext->hContext;

			if (SCardIsValidContext(hContext))
			{
				SCardReleaseContext(hContext);
			}
		}

		free(pKeys);
	}
}