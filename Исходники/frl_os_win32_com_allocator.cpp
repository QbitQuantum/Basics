void* Allocator::operator new( size_t size )
{
	return CoTaskMemAlloc( size);
}