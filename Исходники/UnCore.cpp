// This method will grow array's MaxCount. No items will be allocated.
// The allocated memory is not initialized because items could be inserted
// and removed at any time - so initialization should be performed in
// upper level functions like Insert()
void FArray::GrowArray(int count, int elementSize)
{
	guard(FArray::GrowArray);
	assert(count > 0);

	int prevCount = MaxCount;

	// check for available space
	int newCount = DataCount + count;
	if (newCount > MaxCount)
	{
		// Not enough space, resize ...
		// Allow small initial size of array
		const int minCount = 4;
		if (newCount > minCount)
		{
			MaxCount = Align(DataCount + count, 16) + 16;
		}
		else
		{
			MaxCount = minCount;
		}
		// Align memory block to reduce fragmentation
		int dataSize = Align(MaxCount * elementSize, 16);
		// Recompute MaxCount in a case if alignment increases its capacity
		MaxCount = dataSize / elementSize;
		// Reallocate memory
		if (!IsStatic())
		{
			DataPtr = appRealloc(DataPtr, dataSize);
		}
		else
		{
			// "static" array becomes non-static
			void* oldData = DataPtr; // this is a static pointer
			DataPtr = appMalloc(dataSize);
			memcpy(DataPtr, oldData, prevCount * elementSize);
		}
	}

	unguardf("%d x %d", count, elementSize);
}