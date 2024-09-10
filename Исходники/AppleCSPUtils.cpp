/*
 * Ensure that indicated CssmData can handle 'length' bytes 
 * of data. Malloc the Data ptr if necessary.
 */
void setUpCssmData(
	CssmData			&data,
	size_t				length,
	Allocator		&allocator)
{
	/* FIXME - I'm sure Perry has more elegant ways of doing this,
	 * but I can't figure them out. */
	if(data.Length == 0) {
		data.Data = (uint8 *)allocator.malloc(length);
	}
	else if(data.Length < length) {
		CssmError::throwMe(CSSMERR_CSP_INVALID_DATA);
	}
	data.Length = length;
}