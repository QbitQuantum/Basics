/**
 * The rename function updates the filename.
 */
int pcsl_file_rename(const pcsl_string * oldName, 
		     const pcsl_string * newName)
{
    int res;
    int status;
    const jchar * pszOldFilename = pcsl_string_get_utf16_data(oldName);

    if(pszOldFilename == NULL) {
	return -1;
    } else {
      const jchar * pszNewFilename = pcsl_string_get_utf16_data(newName);

      if(pszNewFilename == NULL) {
        pcsl_string_release_utf16_data(pszOldFilename, oldName);
	return -1;
      }

      res = _wrename(pszOldFilename, pszNewFilename);
      if(res < 0) {
	status = -1;
      } else {
	status = 0;
      }

      return status;
    }
}