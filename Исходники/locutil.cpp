const Hashtable *
LocaleUtility::getAvailableLocaleNames(const UnicodeString & bundleID)
{
	// LocaleUtility_cache is a hash-of-hashes.  The top-level keys
	// are path strings ('bundleID') passed to
	// ures_openAvailableLocales.  The top-level values are
	// second-level hashes.  The second-level keys are result strings
	// from ures_openAvailableLocales.  The second-level values are
	// garbage ((void*)1 or other random pointer).

	UErrorCode status = U_ZERO_ERROR;
	Hashtable * cache;
	umtx_lock(NULL);
	cache = LocaleUtility_cache;
	umtx_unlock(NULL);

	if (cache == NULL)
	{
		cache = new Hashtable(status);
		if (cache == NULL || U_FAILURE(status))
		{
			return NULL; // catastrophic failure; e.g. out of memory
		}
		cache->setValueDeleter(uhash_deleteHashtable);
		Hashtable * h; // set this to final LocaleUtility_cache value
		umtx_lock(NULL);
		h = LocaleUtility_cache;
		if (h == NULL)
		{
			LocaleUtility_cache = h = cache;
			cache = NULL;
			ucln_common_registerCleanup(UCLN_COMMON_SERVICE, service_cleanup);
		}
		umtx_unlock(NULL);
		if (cache != NULL)
		{
			delete cache;
		}
		cache = h;
	}

	U_ASSERT(cache != NULL);

	Hashtable * htp;
	umtx_lock(NULL);
	htp = (Hashtable *) cache->get(bundleID);
	umtx_unlock(NULL);

	if (htp == NULL)
	{
		htp = new Hashtable(status);
		if (htp && U_SUCCESS(status))
		{
			CharString cbundleID;
			cbundleID.appendInvariantChars(bundleID, status);
			const char * path = cbundleID.isEmpty() ? NULL : cbundleID.data();
			UEnumeration * uenum = ures_openAvailableLocales(path, &status);
			for (;;)
			{
				const UChar * id = uenum_unext(uenum, NULL, &status);
				if (id == NULL)
				{
					break;
				}
				htp->put(UnicodeString(id), (void *)htp, status);
			}
			uenum_close(uenum);
			if (U_FAILURE(status))
			{
				delete htp;
				return NULL;
			}
			umtx_lock(NULL);
			cache->put(bundleID, (void *)htp, status);
			umtx_unlock(NULL);
		}
	}
	return htp;
}