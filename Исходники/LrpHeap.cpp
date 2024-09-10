CLrpHeap::CLrpHeap() : m_heap(HeapCreate(0, 0, 0))
{
	if (nullptr == m_heap)
	{
		throw runtime_error("Couldn't create a new memory heap");
	}
}