TInt CParsedFieldCollection::GetFieldValueAndLength(const TDesC& aFieldName, TPtrC& aValue) const
	{
	aValue.Set(GetFieldValue(aFieldName));
	return aValue.Length();
	}