char *logger_alloc_copy_string(const char *str) {
    logger_assert(NULL != str);

    size_t size = strnlen_s(str, RSIZE_MAX_STR);
    char *buffer = logger_memory_alloc(size + 1);
    if (NULL != buffer) {
        strncpy_s(buffer, RSIZE_MAX_STR, str, size);
        buffer[size] = '\0';
    }

    return buffer;
}