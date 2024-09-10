void OsMemory_free_chunk(address chunk_ptr) {
    VirtualFree(chunk_ptr, 0, MEM_RELEASE);
}