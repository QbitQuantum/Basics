BioAPI_RETURN BioAPI mdsutil_GetRecord(CSSM_DL_DB_HANDLE hDLDB,
									  CSSM_QUERY Query,
									  CSSM_DB_RECORDTYPE RecordType,
									  uint32 NumAttributes,
									  CSSM_HANDLE_PTR ResultsHandle,
									  CSSM_DB_ATTRIBUTE_DATA *OutputAttributeData)
{
	CSSM_DB_UNIQUE_RECORD_PTR RecordId = NULL;
	CSSM_DB_RECORD_ATTRIBUTE_DATA OutputAttributes;
	BioAPI_RETURN retValue = CSSM_OK;

	memset (&OutputAttributes, 0, sizeof (CSSM_DB_RECORD_ATTRIBUTE_DATA));

	/* We want to get NumAttributes back */
	OutputAttributes.DataRecordType = RecordType;
	OutputAttributes.NumberOfAttributes = NumAttributes;
	OutputAttributes.AttributeData = OutputAttributeData;

	if (0 == *ResultsHandle)
	{
		if( !IsBadCodePtr((CSSM_PROC_ADDR)MDSFuncs.DataGetFirst))
		{
			retValue = MDSFuncs.DataGetFirst (hDLDB, /* DLDBHandle */
											  &Query,
											  ResultsHandle,
											  &OutputAttributes,
											  NULL,
											  &RecordId);
		}
	} else {
		if( !IsBadCodePtr((CSSM_PROC_ADDR)MDSFuncs.DataGetNext))
		{
			retValue = MDSFuncs.DataGetNext (hDLDB, /* DLDBHandle */
											 *ResultsHandle,
											 &OutputAttributes,
											 NULL,
											 &RecordId);
		}
	}

	if (retValue != CSSM_OK)
		return retValue;

	if (!IsBadCodePtr((CSSM_PROC_ADDR)MDSFuncs.FreeUniqueRecord))
		MDSFuncs.FreeUniqueRecord(hDLDB, RecordId);

	return (retValue);
}