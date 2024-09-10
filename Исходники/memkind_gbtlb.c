static int ptr_hash(void *ptr, int table_len)
{
    return _mm_crc32_u64(0, (size_t)ptr) % table_len;
}