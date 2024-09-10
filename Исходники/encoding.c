/**
 * How many bytes are needed to convert from an encoding to utf16?
 * @param src the source in the encoding
 * @param srclen its length in bytes
 * @param encoding the src's encoding
 * @return the number of UCHARS needed
 */
int measure_from_encoding( char *src, size_t srclen, char *encoding )
{
    UConverter *conv = NULL;
  	UErrorCode status = U_ZERO_ERROR;
  	int32_t len=0;
  	
	conv = ucnv_open( encoding, &status );
  	if ( status == U_ZERO_ERROR )
	{	
	  	len = ucnv_toUChars( conv, NULL, 0, src, srclen, &status );
	  	if ( status != U_BUFFER_OVERFLOW_ERROR )
        {
            printf("encoding: %s\n",u_errorName(status));
            len = 0;
        }
        ucnv_close(conv);
	}
    return len;
}