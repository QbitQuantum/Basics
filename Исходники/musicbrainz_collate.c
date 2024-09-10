static int32_t
sortkey_from_unicode (UChar *input, uint8_t **output)
{
    UErrorCode status = U_ZERO_ERROR;
    UCollator * collator = ucol_open ("", &status);
    int32_t size;

    if (icu_failure (status))
        return 0;

    ucol_setAttribute (collator, UCOL_NUMERIC_COLLATION, UCOL_ON, &status);

    if (icu_failure (status))
        return 0;

    *output = (uint8_t *) palloc (sizeof (uint8_t) * PREALLOC_SIZE);
    size = ucol_getSortKey (collator, input, -1, *output, PREALLOC_SIZE);

    if (size > PREALLOC_SIZE)
    {
        pfree (*output);
        *output = (uint8_t *) palloc (sizeof (uint8_t) * size);
        ucol_getSortKey (collator, input, -1, *output, size);
    }

    ucol_close (collator);

    if (size < 1)
    {
        ereport(ERROR, (errmsg("ICU sortkey is zero")));
    }

    return size;
}