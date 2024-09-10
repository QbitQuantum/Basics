void
NativeCodeData::AddFixupEntryForPointerArray(void* startAddress, DataChunk * chunkList)
{
    DataChunk* chunk = NativeCodeData::GetDataChunk(startAddress);
    Assert(chunk->len % sizeof(void*) == 0);
    for (unsigned int i = 0; i < chunk->len / sizeof(void*); i++)
    {
        size_t offset = i * sizeof(void*);
        void* targetAddr = *(void**)((char*)startAddress + offset);

        if (targetAddr == nullptr)
        {
            continue;
        }

        DataChunk* targetChunk = NativeCodeData::GetDataChunk(targetAddr);

#if DBG
        bool foundTargetChunk = false;
        DataChunk* chunk1 = chunkList;
        while (chunk1 && !foundTargetChunk)
        {
            foundTargetChunk = (chunk1 == targetChunk);
            chunk1 = chunk1->next;
        }
        AssertMsg(foundTargetChunk, "current pointer is not allocated with NativeCodeData allocator?"); // change to valid check instead of assertion?
#endif

        NativeDataFixupEntry* entry = (NativeDataFixupEntry*)midl_user_allocate(sizeof(NativeDataFixupEntry));
        if (!entry)
        {
            Js::Throw::OutOfMemory();
        }
        __analysis_assume(entry);
        entry->addrOffset = (unsigned int)offset;
        entry->targetTotalOffset = targetChunk->offset;
        entry->next = chunk->fixupList;
        chunk->fixupList = entry;

#if DBG
        if (PHASE_TRACE1(Js::NativeCodeDataPhase))
        {
            Output::Print(L"NativeCodeData Add Fixup: %p[%d](+%d, chunk:%p)  -->  %p(chunk:%p)  %S\n",
                startAddress, i, entry->addrOffset, (void*)chunk, targetAddr, (void*)targetChunk, chunk->dataType);
        }
#endif
    }
}