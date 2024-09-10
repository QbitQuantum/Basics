int FRemapTable::StoreTranslation()
{
	unsigned int i;

	for (i = 0; i < translationtables[TRANSLATION_Decorate].Size(); i++)
	{
		if (*this == *translationtables[TRANSLATION_Decorate][i])
		{
			// A duplicate of this translation already exists
			return TRANSLATION(TRANSLATION_Decorate, i);
		}
	}
	if (translationtables[TRANSLATION_Decorate].Size() >= MAX_DECORATE_TRANSLATIONS)
	{
		I_Error("Too many DECORATE translations");
	}
	FRemapTable *newtrans = new FRemapTable;
	*newtrans = *this;
	i = translationtables[TRANSLATION_Decorate].Push(newtrans);
	return TRANSLATION(TRANSLATION_Decorate, i);
}