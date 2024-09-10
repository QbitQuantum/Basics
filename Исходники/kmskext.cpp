inline void RemoveAndCompress(RArray<T>& aContainer, TInt aIndex)
/**
	Remove the indexed item from the supplied array and compress
	the array.
	
	Without compression, the memory at the end of the array will
	not be freed.  Unless the memory is freed, memory leak testing
	will fail.
	
	@param	aContainer		Array from which item must be removed.
	@param	aIndex			Item to remove from array.
 */
	{
	aContainer.Remove(aIndex);
	aContainer.Compress();
	}