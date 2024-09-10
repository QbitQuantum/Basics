CURLcode FindWin32CACert(struct Configurable *config, const char *bundle_file)
{
  CURLcode result = CURLE_OK;

  /* search and set cert file only if libcurl supports SSL */
  if(curlinfo->features & CURL_VERSION_SSL) {

    DWORD res_len;
    DWORD buf_tchar_size = PATH_MAX + 1;
    DWORD buf_bytes_size = sizeof(TCHAR) * buf_tchar_size;
    char *ptr = NULL;

    char *buf = malloc(buf_bytes_size);
    if(!buf)
      return CURLE_OUT_OF_MEMORY;
    buf[0] = '\0';

    res_len = SearchPathA(NULL, bundle_file, NULL, buf_tchar_size, buf, &ptr);
    if(res_len > 0) {
      Curl_safefree(config->cacert);
      config->cacert = strdup(buf);
      if(!config->cacert)
        result = CURLE_OUT_OF_MEMORY;
    }

    Curl_safefree(buf);
  }

  return result;
}