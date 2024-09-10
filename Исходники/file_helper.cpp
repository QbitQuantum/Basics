void free_file(BYTE* buffer, size_t buffer_size)
{
    VirtualFree(buffer, buffer_size, MEM_RELEASE);
}