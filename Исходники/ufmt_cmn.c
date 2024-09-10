void *
ufmt_utop(const UChar     *buffer,
          int32_t     *len)
{
    int32_t count, resultIdx, incVal, offset;
    /* This union allows the pointer to be written as an array. */
    union {
        void *ptr;
        uint8_t bytes[sizeof(void*)];
    } result;
    
    /* intialize variables */
    count      = 0;
    offset     = 0;
    result.ptr = NULL;

    /* Skip the leading zeros */
    while(buffer[count] == DIGIT_0 || u_isspace(buffer[count])) {
        count++;
        offset++;
    }

    /* iterate through buffer, stop when you hit the end */
    while(ufmt_isdigit(buffer[count], 16) && count < *len) {
        /* increment the count consumed */
        ++count;
    }

    /* detect overflow */
    if (count - offset > (int32_t)(sizeof(void*)*NIBBLE_PER_BYTE)) {
        offset = count - (int32_t)(sizeof(void*)*NIBBLE_PER_BYTE);
    }
    
    /* Initialize the direction of the input */
#if U_IS_BIG_ENDIAN
    incVal = -1;
    resultIdx = (int32_t)(sizeof(void*) - 1);
#else
    incVal = 1;
    resultIdx = 0;
#endif
    /* Write how much was consumed. */
    *len = count;
    while(--count >= offset) {
        /* Get the first nibble of the byte */
        uint8_t byte = (uint8_t)ufmt_digitvalue(buffer[count]);

        if (count > offset) {
            /* Get the second nibble of the byte when available */
            byte = (uint8_t)(byte + (ufmt_digitvalue(buffer[--count]) << 4));
        }
        /* Write the byte into the array */
        result.bytes[resultIdx] = byte;
        resultIdx += incVal;
    }

    return result.ptr;
}