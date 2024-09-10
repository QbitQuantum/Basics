double IoSeq_asDouble(IoSeq *self)
{
	return strtod((char *)UArray_bytes(DATA(self)), NULL);
}