size_t fp_write(const void *buf, size_t size, size_t count, void *handle)
{
	return fwrite(buf, size, count, (FILE *)handle);
}