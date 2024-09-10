PVOID WorldChunk::operator new(size_t ourSize)
{
	PVOID result = systemHeap->Malloc(ourSize);
	return(result);
}