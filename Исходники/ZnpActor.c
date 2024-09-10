PZNPACTORDATA ZnpActorMakeData(char* dataName, BYTE nDataType, void* data, BYTE dataLen)
{
	if (dataName == NULL)
		return NULL;
	PZNPACTORDATA pData = malloc(sizeof(ZNPACTORDATA));
	pData->dataName = StrDup(dataName);
	pData->nDataType = nDataType;
	switch (nDataType)
	{
	case ZNP_DATA_TYPE_STRING:
		pData->value = (void*)StrDup((char*)data);
		break;
	case ZNP_DATA_TYPE_INTERGER:
		pData->value = malloc(sizeof(int));
		memset(pData->value, 0, sizeof(int));
		CopyMemory(pData->value, data, dataLen);
		break;
	case ZNP_DATA_TYPE_FLOAT:
		pData->value = malloc(sizeof(double));
		memset(pData->value, 0, sizeof(double));
		CopyMemory(pData->value, data, dataLen);
		break;
	default:
		free(pData->dataName);
		free(pData);
		return NULL;
	}
	return pData;
}