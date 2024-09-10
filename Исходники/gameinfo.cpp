/*
 *   Look up a a value by name, returning a pointer to the value string.
 */
const char *CTadsGameInfo::get_val(const char *name) const
{
    /* for efficiency, note the length of the name up front */
    size_t name_len = strlen(name);

    /* scan our list of value entries for the given name */
    for (tads_valinfo *cur = first_val_ ; cur != 0 ; cur = cur->nxt)
    {
        /* 
         *   If the name matches, return the value for this entry.  Note
         *   that, since the name is always a plain ASCII string, we can
         *   perform a simple byte-by-byte case-insensitive comparison using
         *   memicmp. 
         */
        if (cur->name_len == name_len
            && memicmp(cur->name, name, name_len) == 0)
        {
            /* it's the one - return its value */
            return cur->val;
        }
    }

    /* didn't find it - return null */
    return 0;
}