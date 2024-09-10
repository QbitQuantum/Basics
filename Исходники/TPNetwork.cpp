static CSSM_RETURN tpDecodeCert(
	Allocator		&alloc,
	CSSM_DATA		&rtnBlob)		// will be reallocated if needed
{
	const unsigned char *inbuf = (const unsigned char *)rtnBlob.Data;
	unsigned inlen = (unsigned)rtnBlob.Length;
	unsigned char *outbuf = NULL;
	unsigned outlen = 0;
	CSSM_RETURN ortn = cuConvertPem(inbuf, inlen, &outbuf, &outlen);

	if(ortn == 0 && outbuf != NULL) {
		/* Decoded result needs to be malloc'd via input allocator */
		unsigned char *rtnP = (unsigned char *) alloc.malloc(outlen);
		if(rtnP != NULL) {
			memcpy(rtnP, outbuf, outlen);
			rtnBlob.Data = rtnP;
			rtnBlob.Length = outlen;
		}
		free(outbuf);
		alloc.free((void *)inbuf);
	}
	return ortn;
}