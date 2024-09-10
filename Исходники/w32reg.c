/* Return a string from the Win32 Registry or NULL in case of error.
   Caller must release the return value with g_free ().  A NULL for
   root is an alias for HKEY_CURRENT_USER with a fallback for
   HKEY_LOCAL_MACHINE.  */
char *
read_w32_registry_string (const char *root, const char *dir, const char *name)
{
    HKEY root_key;
    HKEY key_handle;
    DWORD n1;
    DWORD nbytes;
    DWORD type;
    char *result = NULL;

    root_key = get_root_key (root);
    if (! root_key)
        return NULL;

    if (RegOpenKeyEx (root_key, dir, 0, KEY_READ, &key_handle))
    {
        if (root)
            /* No need for a RegClose, so return directly.  */
            return NULL;

        /* It seems to be common practise to fall back to HKLM.  */
        if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, dir, 0, KEY_READ, &key_handle))
            /* Still no need for a RegClose, so return directly.  */
            return NULL;
    }

    nbytes = 1;
    if (RegQueryValueEx (key_handle, name, 0, NULL, NULL, &nbytes))
    {
        if (root)
            goto leave;

        /* Try to fallback to HKLM also for a missing value.  */
        RegCloseKey (key_handle);
        if (RegOpenKeyEx (HKEY_LOCAL_MACHINE, dir, 0, KEY_READ, &key_handle))
            return NULL;

        if (RegQueryValueEx( key_handle, name, 0, NULL, NULL, &nbytes))
            goto leave;
    }
    n1 = nbytes + 1;
    result = g_malloc (n1);
    if (RegQueryValueEx (key_handle, name, 0, &type, result, &n1))
    {
        g_free (result);
        result = NULL;
        goto leave;
    }

    /* Make sure it is really a string.  */
    result[nbytes] = 0;
    if (type == REG_EXPAND_SZ && strchr (result, '%'))
    {
        char *tmp;

        n1 += 1000;
        tmp = g_malloc (n1 + 1);
        nbytes = ExpandEnvironmentStrings (result, tmp, n1);
        if (nbytes && nbytes > n1)
        {
            free (tmp);
            n1 = nbytes;
            tmp = g_malloc (n1 + 1);
            nbytes = ExpandEnvironmentStrings (result, tmp, n1);
            if (nbytes && nbytes > n1)
            {
                /* Oops: truncated, better don't expand at all.  */
                free (tmp);
                goto leave;
            }
            tmp[nbytes] = 0;
            g_free (result);
            result = tmp;
        }
        else if (nbytes)
        {
            /* Okay, reduce the length.  */
            tmp[nbytes] = 0;
            free (result);
            result = g_malloc (strlen (tmp) + 1);
            strcpy (result, tmp);
            g_free (tmp);
        }
        else
        {
            /* Error - don't expand.  */
            g_free (tmp);
        }
    }

leave:
    RegCloseKey (key_handle);
    return result;
}