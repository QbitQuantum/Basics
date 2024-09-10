int main(int argc, const char **argv)
{
	// _fseeki64() and _ftelli64() use __int64.
	// NOTE: __int64 is an MSVC-proprietary type.
	__int64 offset = _ftelli64(NULL);
	_fseeki64(NULL, offset, SEEK_SET);
	return 0;
}