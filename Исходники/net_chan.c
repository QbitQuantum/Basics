/*
http://www.zlib.net/manual.html#compress2
int compress2 (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level);
Compresses the source buffer into the destination buffer. The level parameter has the same meaning
as in deflateInit. sourceLen is the byte length of the source buffer. Upon entry, destLen is the
total size of the destination buffer, which must be at least 0.1% larger than sourceLen plus 12 bytes.
Upon exit, destLen is the actual size of the compressed buffer.

compress2 returns Z_OK if success, Z_MEM_ERROR if there was not enough memory, Z_BUF_ERROR if there
was not enough room in the output buffer, Z_STREAM_ERROR if the level parameter is invalid.
*/
static int Netchan_ZLibCompressChunk( const uint8_t *source, unsigned long sourceLen, uint8_t *dest, unsigned long destLen,
									 int level, int wbits )
{
	int result, zlerror;

	zlerror = compress2( dest, &destLen, source, sourceLen, level );
	switch( zlerror )
	{
	case Z_OK:
		result = destLen; // returns the new length into destLen
		break;
	case Z_MEM_ERROR:
		Com_DPrintf( "ZLib data error! Z_MEM_ERROR on compress.\n" );
		result = -1;
		break;
	case Z_BUF_ERROR:
		Com_DPrintf( "ZLib data error! Z_BUF_ERROR on compress.\n" );
		result = -1;
		break;
	case Z_STREAM_ERROR:
		Com_DPrintf( "ZLib data error! Z_STREAM_ERROR on compress.\n" );
		result = -1;
		break;
	default:
		Com_DPrintf( "ZLib data error! Error code %i on compress.\n", zlerror );
		result = -1;
		break;
	}

	return result;
}