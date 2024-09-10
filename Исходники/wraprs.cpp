void* align_base_64::operator new[](size_t bytes)
{
	return _aligned_malloc(bytes, 64);
}