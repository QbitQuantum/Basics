/**
 * name:	CLineBuffer::operator +
 * desc:	appends the specified double word integer as a string to the class's _pVal member
 * param:	dVal	-	double word integer whose value to add
 *
 * return:	length of the string, added
 **/
size_t CLineBuffer::operator + (const DWORD dVal)
{
	size_t cbLength = 10;
	
	if (_resizeBuf(cbLength)) {
		cbLength = mir_strlen(_ltoa(dVal, (LPSTR)(_pVal + _cbUsed), 10));
		_cbUsed += cbLength;
		return	cbLength;
	}
	return 0;
}