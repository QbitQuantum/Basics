double BinaryReaderBE::ReadDouble()
{
	u64 ret = _byteswap_uint64(BinaryReader::ReadUInt64());
	return *((double *) &ret);
}