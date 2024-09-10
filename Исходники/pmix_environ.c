/*
 * Portable version of setenv(), allowing editing of any environ-like
 * array
 */
pmix_status_t pmix_setenv(const char *name, const char *value, bool overwrite,
                          char ***env)
{
    int i;
    char *newvalue, *compare;
    size_t len;

    /* Make the new value */

    if (NULL == value) {
        i = asprintf(&newvalue, "%s=", name);
    } else {
        i = asprintf(&newvalue, "%s=%s", name, value);
    }
    if (NULL == newvalue || 0 > i) {
        return PMIX_ERR_OUT_OF_RESOURCE;
    }

    /* Check the bozo case */

    if( NULL == env ) {
        return PMIX_ERR_BAD_PARAM;
    } else if (NULL == *env) {
        i = 0;
        pmix_argv_append(&i, env, newvalue);
        free(newvalue);
        return PMIX_SUCCESS;
    }

    /* If this is the "environ" array, use putenv */
    if( *env == environ ) {
        /* THIS IS POTENTIALLY A MEMORY LEAK!  But I am doing it
           because so that we don't violate the law of least
           astonishmet for PMIX developers (i.e., those that don't
           check the return code of pmix_setenv() and notice that we
           returned an error if you passed in the real environ) */
        putenv(newvalue);
        return PMIX_SUCCESS;
    }

    /* Make something easy to compare to */

    i = asprintf(&compare, "%s=", name);
    if (NULL == compare || 0 > i) {
        free(newvalue);
        return PMIX_ERR_OUT_OF_RESOURCE;
    }
    len = strlen(compare);

    /* Look for a duplicate that's already set in the env */

    for (i = 0; (*env)[i] != NULL; ++i) {
        if (0 == strncmp((*env)[i], compare, len)) {
            if (overwrite) {
                free((*env)[i]);
                (*env)[i] = newvalue;
                free(compare);
                return PMIX_SUCCESS;
            } else {
                free(compare);
                free(newvalue);
                return PMIX_EXISTS;
            }
        }
    }

    /* If we found no match, append this value */

    i = pmix_argv_count(*env);
    pmix_argv_append(&i, env, newvalue);

    /* All done */

    free(compare);
    free(newvalue);
    return PMIX_SUCCESS;
}