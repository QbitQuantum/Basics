void SmallSizeMemoryPool::Push(MemAllocInfo* ptr)
{
	InterlockedPushEntrySList(&mFreeList, (PSLIST_ENTRY)ptr);
	InterlockedDecrement(&mAllocCount);
}