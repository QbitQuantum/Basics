void
MetaAttribute::unpackAttribute(const ReadSection &rs, Allocator &allocator,
	uint32 &numValues, CSSM_DATA *&values) const
{
	uint32 valueOffset;
	unpackNumberOfValues(rs, numValues, valueOffset);
	
	// Rough check for number of values; will be more like 10 or 20
	if (numValues > 1024)
		CssmError::throwMe(CSSMERR_DL_DATABASE_CORRUPT);

	values = reinterpret_cast<CSSM_DATA *>(allocator.malloc(numValues * sizeof(CSSM_DATA)));
	
	for (uint32 i = 0; i < numValues; i++)
		unpackValue(rs, valueOffset, values[i], allocator);
}