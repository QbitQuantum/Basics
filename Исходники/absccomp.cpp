//------------------------------------------------------------------------------
void AMemory::Deallocate(void)
{
	if(mHeap)
	{
		free(mHeap);
		mHeap = 0x0;
		mSize = 0;
	}
}