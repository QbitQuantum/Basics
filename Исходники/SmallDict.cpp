void ff::SmallDict::Reserve(size_t newAllocated, bool allowEmptySpace)
{
	size_t oldAllocated = Allocated();
	if (newAllocated > oldAllocated)
	{
		if (allowEmptySpace)
		{
			newAllocated = std::max<size_t>(NearestPowerOfTwo(newAllocated), 4);
		}

		size_t byteSize = sizeof(Data) + newAllocated * sizeof(Entry) - sizeof(Entry);
		_data = (Data *)_aligned_realloc(_data, byteSize, __alignof(Data));
		_data->allocated = newAllocated;
		_data->size = oldAllocated ? _data->size : 0;
		_data->atomizer = oldAllocated ? _data->atomizer : &ProcessGlobals::Get()->GetStringCache();
	}
}