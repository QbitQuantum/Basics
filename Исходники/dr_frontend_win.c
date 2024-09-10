/* Implements a normal path search for fname on the paths in env_var. Resolves symlinks,
 * which is needed to get the right config filename (i#1062).
 */
drfront_status_t
drfront_searchenv(const char *fname, const char *env_var, OUT char *full_path,
                  const size_t full_path_size, OUT bool *ret)
{
    drfront_status_t status_check = DRFRONT_ERROR;
    size_t size_needed = 0;
    TCHAR wfname[MAX_PATH];
    /* XXX: Not sure what the size for environment variable names should be.
     *      Perhaps we want a drfront_char_to_tchar_size_needed
     */
    TCHAR wenv_var[MAX_PATH];
    TCHAR wfull_path[MAX_PATH];

    if (full_path == NULL && ret == NULL)
        return DRFRONT_ERROR_INVALID_PARAMETER;

    status_check = drfront_char_to_tchar(fname, wfname, BUFFER_SIZE_ELEMENTS(wfname));
    if (status_check != DRFRONT_SUCCESS) {
        *ret = false;
        return status_check;
    }
    status_check = drfront_char_to_tchar(env_var, wenv_var,
                                         BUFFER_SIZE_ELEMENTS(wenv_var));
    if (status_check != DRFRONT_SUCCESS) {
        *ret = false;
        return status_check;
    }

    _wsearchenv(wfname, wenv_var, wfull_path);

    if (wfull_path[0] == L'\0') {
        *ret = false;
        return DRFRONT_ERROR;
    }

    status_check = drfront_tchar_to_char_size_needed(wfull_path, &size_needed);
    if (status_check != DRFRONT_SUCCESS) {
        *ret = false;
        return status_check;
    } else if (full_path_size < size_needed) {
        *ret = true;
        return DRFRONT_ERROR_INVALID_SIZE;
    }

    status_check = drfront_tchar_to_char(wfull_path, full_path, full_path_size);
    if (status_check != DRFRONT_SUCCESS) {
        *ret = false;
        return status_check;
    }
    full_path[full_path_size - 1] = '\0';
    *ret = true;
    return DRFRONT_SUCCESS;
}