static SHMByteArray* shm_allocate_bytes(size_t size)
{
    SharedMemoryPool* pool =
        SharedMemoryPoolHolder<IPC_FIFO_SHM_POOL>::GetSharedMemoryPool();
    SHMByteArray* array = NULL;
    void* mem = pool->Malloc(sizeof(SHMByteArray));
    RETURN_NULL_IF_NULL(mem);
    try
    {
        array = new (mem) SHMByteArray(pool,
                                       size < kDefaultByteArrayChunkSize ? size
                                       : kDefaultByteArrayChunkSize);
        return array;
    } catch (Exception& e)
    {
        ERROR_LOG("Failed to initialize a shm byte array with size:%u", size);
        //mm_free(pool, mem);
        pool->Free(mem);
        return NULL;
    }
}