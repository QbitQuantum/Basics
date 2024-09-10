static void* lzham_default_realloc(void* p, size_t size, size_t* pActual_size, lzham_bool movable, void* pUser_data)
{
    LZHAM_NOTE_UNUSED(pUser_data);

    void* p_new;

    if (!p)
    {
        p_new = malloc(size);
        LZHAM_ASSERT( (reinterpret_cast<ptr_bits_t>(p_new) & (LZHAM_MIN_ALLOC_ALIGNMENT - 1)) == 0 );

        if (pActual_size)
            *pActual_size = p_new ? _msize(p_new) : 0;
    }
    else if (!size)
    {
        free(p);
        p_new = NULL;

        if (pActual_size)
            *pActual_size = 0;
    }
    else
    {
        void* p_final_block = p;
#ifdef WIN32
        p_new = _expand(p, size);
#else

        p_new = NULL;
#endif

        if (p_new)
        {
            LZHAM_ASSERT( (reinterpret_cast<ptr_bits_t>(p_new) & (LZHAM_MIN_ALLOC_ALIGNMENT - 1)) == 0 );
            p_final_block = p_new;
        }
        else if (movable)
        {
            p_new = realloc(p, size);

            if (p_new)
            {
                LZHAM_ASSERT( (reinterpret_cast<ptr_bits_t>(p_new) & (LZHAM_MIN_ALLOC_ALIGNMENT - 1)) == 0 );
                p_final_block = p_new;
            }
        }

        if (pActual_size)
            *pActual_size = _msize(p_final_block);
    }

    return p_new;
}