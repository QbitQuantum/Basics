void *
__gf_realloc (void *ptr, size_t size)
{
        size_t          tot_size = 0;
        char            *orig_ptr = NULL;
        xlator_t        *xl = NULL;
        uint32_t        type = 0;
        char            *new_ptr;

        if (!THIS->ctx->mem_acct_enable)
                return REALLOC (ptr, size);

        REQUIRE(NULL != ptr);

        tot_size = size + GF_MEM_HEADER_SIZE + GF_MEM_TRAILER_SIZE;

        orig_ptr = (char *)ptr - 8 - 4;

        GF_ASSERT (*(uint32_t *)orig_ptr == GF_MEM_HEADER_MAGIC);

        orig_ptr = orig_ptr - sizeof(xlator_t *);
        xl = *((xlator_t **)orig_ptr);

        orig_ptr = (char *)ptr - GF_MEM_HEADER_SIZE;
        type = *(uint32_t *)orig_ptr;

        new_ptr = realloc (orig_ptr, tot_size);
        if (!new_ptr) {
                gf_log_nomem ("", GF_LOG_ALERT, tot_size);
                return NULL;
        }

        /*
         * We used to pass (char **)&ptr as the second
         * argument after the value of realloc was saved
         * in ptr, but the compiler warnings complained
         * about the casting to and forth from void ** to
         * char **.
         */
        gf_mem_set_acct_info (xl, &new_ptr, size, type);

        return (void *)new_ptr;
}