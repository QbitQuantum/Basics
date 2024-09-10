static const UChar * u_file_translit(UFILE *f, const UChar *src, int32_t *count, UBool flush)
{
    int32_t newlen;
    int32_t junkCount = 0;
    int32_t textLength;
    int32_t textLimit;
    UTransPosition pos;
    UErrorCode status = U_ZERO_ERROR;

    if(count == NULL)
    {
        count = &junkCount;
    }

    if ((!f)||(!f->fTranslit)||(!f->fTranslit->translit))
    {
        /* fast path */
        return src;
    }

    /* First: slide over everything */
    if(f->fTranslit->length > f->fTranslit->pos)
    {
        memmove(f->fTranslit->buffer, f->fTranslit->buffer + f->fTranslit->pos,
            (f->fTranslit->length - f->fTranslit->pos)*sizeof(UChar));
    }
    f->fTranslit->length -= f->fTranslit->pos; /* always */
    f->fTranslit->pos = 0;

    /* Calculate new buffer size needed */
    newlen = (*count + f->fTranslit->length) * 4;

    if(newlen > f->fTranslit->capacity)
    {
        if(f->fTranslit->buffer == NULL)
        {
            f->fTranslit->buffer = (UChar*)uprv_malloc(newlen * sizeof(UChar));
        }
        else
        {
            f->fTranslit->buffer = (UChar*)uprv_realloc(f->fTranslit->buffer, newlen * sizeof(UChar));
        }
        f->fTranslit->capacity = newlen;
    }

    /* Now, copy any data over */
    u_strncpy(f->fTranslit->buffer + f->fTranslit->length,
        src,
        *count);
    f->fTranslit->length += *count;

    /* Now, translit in place as much as we can  */
    if(flush == FALSE)
    {
        textLength = f->fTranslit->length;
        pos.contextStart = 0;
        pos.contextLimit = textLength;
        pos.start        = 0;
        pos.limit        = textLength;

        utrans_transIncrementalUChars(f->fTranslit->translit,
            f->fTranslit->buffer, /* because we shifted */
            &textLength,
            f->fTranslit->capacity,
            &pos,
            &status);

#ifdef _DEBUG
        if(U_FAILURE(status))
        {
            fprintf(stderr, " Gack. Translit blew up with a %s\n", u_errorName(status));
            return src;
        }
#endif

        /* now: start/limit point to the transliterated text */
        /* Transliterated is [buffer..pos.start) */
        *count            = pos.start;
        f->fTranslit->pos = pos.start;
        f->fTranslit->length = pos.limit;

        return f->fTranslit->buffer;
    }
    else
    {
        textLength = f->fTranslit->length;
        textLimit = f->fTranslit->length;

        utrans_transUChars(f->fTranslit->translit,
            f->fTranslit->buffer,
            &textLength,
            f->fTranslit->capacity,
            0,
            &textLimit,
            &status);

#ifdef _DEBUG
        if(U_FAILURE(status))
        {
            fprintf(stderr, " Gack. Translit(flush) blew up with a %s\n", u_errorName(status));
            return src;
        }
#endif

        /* out: converted len */
        *count = textLimit;

        /* Set pointers to 0 */
        f->fTranslit->pos = 0;
        f->fTranslit->length = 0;

        return f->fTranslit->buffer;
    }
}