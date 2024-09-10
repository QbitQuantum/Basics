long x_seek(long offset, int handle, int seekmode)
{
	long result;

#if USE_gemdos
	result = gemdos(66, offset, handle, seekmode);
#else
	result = Fseek(offset, handle, seekmode);
#endif

	return (result < 0) ? (long) xerror((int) result) : result;
}