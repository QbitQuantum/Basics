int memkind_thread_get_arena(struct memkind *kind, unsigned int *arena, size_t size)
{
    static __thread unsigned int MEMKIND_TLS_MODEL arena_tls = UINT_MAX;
    int err = 0;

    if (arena_tls == UINT_MAX) {
        arena_tls = _mm_crc32_u64(0, (uint64_t)pthread_self());
    }
    if (kind->arena_map != NULL) {
        *arena = kind->arena_map[arena_tls % kind->arena_map_len];
    }
    else {
        err = MEMKIND_ERROR_RUNTIME;
    }
    return err;
}