/**
 * \brief Moves chars to the right of \a at to the cache.
 *
 * \param[in,out]  from Char array containing the chars to be moved.
 * \param[in] in Point along \a from[] that marks the split point
 */
void moveToCache(char from[], int at)
{
    int i, j, len;

    len = strLen(from);
    for (i = at+1, j = strLen(cache); i < len && cacheFreeSpace > 0; i++, j++) {
        cache[j] = from[i];
        from[i] = '\0';
        if (cache[j] == '\n')
            j--;
    }
}