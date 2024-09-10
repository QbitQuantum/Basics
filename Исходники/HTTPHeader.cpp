// return a modified accept-encoding header, based on the one supplied,
// but with "identity" added and only supported encodings allowed.
String HTTPHeader::modifyEncodings(String e)
{

	// There are 4 types of encoding: gzip, deflate, compress and identity
	// deflate is in zlib format
	// compress is in unix compress format
	// identity is uncompressed and supported by all browsers (obviously)
	// we do not support compress

	e.toLower();
	String o("Accept-Encoding: identity");
#if ZLIB_VERNUM < 0x1210
#warning 'Accept-Encoding: gzip' is disabled
#else
	if (e.contains("gzip")) {
		o += ",gzip";
	}
#endif
	if (e.contains("deflate")) {
		o += ",deflate";
	}

	return o;
}