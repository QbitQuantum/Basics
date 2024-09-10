long     ZCALLBACK fseek64_file_func(voidpf opaque, voidpf stream, ZPOS64_T offset, int origin)
{
	return _fseeki64((FILE*)stream, offset, origin);
}