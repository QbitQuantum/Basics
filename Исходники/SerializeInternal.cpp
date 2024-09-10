	static void _serializeDouble(ISerialize * nSerialize, double * nValue, const wchar_t * nName, double nOptimal)
	{
		SerializeInternal * serializeInternal = reinterpret_cast<SerializeInternal *>(nSerialize->mSerialize);
		serializeInternal->_serialize((*nValue), nName, nOptimal);
	}