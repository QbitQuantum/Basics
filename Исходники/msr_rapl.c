int rapl_storage(struct rapl_data **data, uint64_t **flags)
{
    static struct rapl_data *rapl = NULL;
    static uint64_t *rapl_flags = NULL;
    static uint64_t sockets = 0;
    static int init = 0;

#ifdef STORAGE_DEBUG
    fprintf(stderr, "%s %s::%d DEBUG: (rapl_storage) data pointer is %p, flags pointer is %p, data is at %p, flags are %lx at %p\n", getenv("HOSTNAME"), __FILE__, __LINE__, data, flags, rapl, (rapl_flags ? *rapl_flags : 0), rapl_flags);
#endif

    if (!init)
    {
        init = 1;
        sockets = num_sockets();

        rapl = (struct rapl_data *) libmsr_malloc(sockets * sizeof(struct rapl_data));
        rapl_flags = (uint64_t *) libmsr_malloc(sizeof(uint64_t));

        if (setflags(rapl_flags))
        {
            return -1;
        }
        if (data != NULL)
        {
            *data = rapl;
        }
        if (flags != NULL)
        {
            *flags = rapl_flags;
        }
#ifdef LIBMSR_DEBUG
        fprintf(stderr, "%s %s::%d DEBUG: (storage) initialized rapl data at %p, flags are %lx, (flags at %p, rapl_flags at %p\n", getenv("HOSTNAME"), __FILE__, __LINE__, rapl, **flags, flags, rapl_flags);
        fprintf(stderr, "DEBUG: socket 0 has pkg_bits at %p\n", &rapl[0].pkg_bits);
#endif
        return 0;
    }
    /* If the data pointer is not null, it should point to the rapl array. */
    if (data != NULL)
    {
        *data = rapl;
    }
    /* if the flags pointer is not null, it should point to the rapl flags. */
    if (flags != NULL)
    {
        *flags = rapl_flags;
    }
    return 0;
}