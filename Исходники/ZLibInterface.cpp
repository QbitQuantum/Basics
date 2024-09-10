/**
Compresses a source buffer into a target buffer, using the ZLib library. 
On success, the target buffer contains a GZIP compatible layout.
Upon entry, target_size is the total size of the destination buffer, 
which must be at least 0.1% larger than source_size plus 24 bytes. 

@param target Destination buffer
@param target_size Size of the destination buffer, in bytes
@param source Source buffer
@param source_size Size of the source buffer, in bytes
@return Returns the actual size of the compressed buffer, returns 0 if an error occured
@see FreeImage_ZLibCompress
*/
DWORD DLL_CALLCONV 
FreeImage_ZLibGZip(BYTE *target, DWORD target_size, BYTE *source, DWORD source_size) {
	uLongf dest_len = (uLongf)target_size - 12;
	DWORD crc = crc32(0L, NULL, 0);

    // set up header (stolen from zlib/gzio.c)
    sprintf((char *)target, "%c%c%c%c%c%c%c%c", 0x1f, 0x8b,
         Z_DEFLATED, 0 /*flags*/, 0,0,0,0 /*time*/);
    int zerr = compress2(target + 8, &dest_len, source, source_size, Z_BEST_COMPRESSION);
	switch(zerr) {
		case Z_MEM_ERROR:	// not enough memory
		case Z_BUF_ERROR:	// not enough room in the output buffer
			FreeImage_OutputMessageProc(FIF_UNKNOWN, "Zlib error : %s", zError(zerr));
			return 0;
        case Z_OK: {
            // patch header, setup crc and length (stolen from mod_trace_output)
            BYTE *p = target + 8; *p++ = 2; *p = OS_CODE; // xflags, os_code
 	        crc = crc32(crc, source, source_size);
	        memcpy(target + 4 + dest_len, &crc, 4);
	        memcpy(target + 8 + dest_len, &source_size, 4);
            return dest_len + 12;
        }
	}
	return 0;
}