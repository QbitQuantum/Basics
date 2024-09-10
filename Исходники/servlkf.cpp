void
LocaleKeyFactory::updateVisibleIDs(Hashtable & result, UErrorCode & status) const
{
	const Hashtable * supported = getSupportedIDs(status);
	if (supported)
	{
		UBool visible = (_coverage & 0x1) == 0;

		const UHashElement * elem = NULL;
		int32_t pos = 0;
		while ((elem = supported->nextElement(pos)) != NULL)
		{
			const UnicodeString & id = *((const UnicodeString *)elem->key.pointer);
			if (!visible)
			{
				result.remove(id);
			}
			else
			{
				result.put(id, (void *)this, status); // this is dummy non-void marker used for set semantics
				if (U_FAILURE(status))
				{
					break;
				}
			}
		}
	}
}