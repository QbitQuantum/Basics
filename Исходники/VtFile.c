int VtFile_rescanHash(struct VtFile *file_scan,
                      const char *hash,
                      time_t rescan_date, int period, int repeat,
                      const char *notify_url, bool notify_changes_only) {

  CURL *curl;
  CURLcode res;
  int ret = 0;
  struct curl_httppost *formpost=NULL;
  struct curl_httppost *lastptr=NULL;
  struct curl_slist *headerlist=NULL;
  char buff[32];
  struct tm time_result;
  static const char header_buf[] = "Expect:";
  long http_response_code = 0;

  VtApiPage_resetBuffer((struct VtApiPage *) file_scan);

  curl = curl_easy_init();
  if (!curl) {
    VT_ERROR("init curl\n");
    goto cleanup;
  }
  // initialize custom header list (stating that Expect: 100-continue is not wanted
  headerlist = curl_slist_append(headerlist, header_buf);

  DBG(1, "hash to rescan'%s'\n", hash);
  DBG(1, "Api Key =  '%s'\n", file_scan->api_key);

  ret = curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "resource",
                     CURLFORM_COPYCONTENTS,  hash,
                     CURLFORM_END);
  if (ret)
    VT_ERROR("Adding hash %s\n", hash);

  if (rescan_date) {
#ifdef WINDOWS
    if (!gmtime_s(&time_result, &rescan_date)) {
      VT_ERROR("Converting time\n");
      goto cleanup;
    }
#else
    if (!gmtime_r(&rescan_date, &time_result)) {
      VT_ERROR("Converting time\n");
      goto cleanup;
    }
#endif

    ret = strftime(buff, sizeof(buff)-1, "%Y%m%d%H%M%S", &time_result);
    ret = curl_formadd(&formpost,
                       &lastptr,
                       CURLFORM_COPYNAME, "date",
                       CURLFORM_COPYCONTENTS,  buff,
                       CURLFORM_END);
    if (ret)
      VT_ERROR("Adding date %s\n", buff);
  }

  if (period) {
    snprintf(buff, sizeof(buff) -1, "%d", period);
    ret = curl_formadd(&formpost,
                       &lastptr,
                       CURLFORM_COPYNAME, "period",
                       CURLFORM_COPYCONTENTS,  buff,
                       CURLFORM_END);
    if (ret)
      VT_ERROR("Adding period %s\n", buff);
  }

  if (repeat) {
    snprintf(buff, sizeof(buff) - 1 , "%d", repeat);
    ret = curl_formadd(&formpost,
                       &lastptr,
                       CURLFORM_COPYNAME, "repeat",
                       CURLFORM_COPYCONTENTS,  buff,
                       CURLFORM_END);
    if (ret)
      VT_ERROR("Adding repeat %s\n", buff);
  }

  if (notify_url) {
    ret = curl_formadd(&formpost,
                       &lastptr,
                       CURLFORM_COPYNAME, "notify_url",
                       CURLFORM_COPYCONTENTS,  notify_url,
                       CURLFORM_END);
    if (ret)
      VT_ERROR("Adding notify_url %s\n", notify_url);

    if (notify_changes_only) {
      ret = curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, "notify_changes_only",
                         CURLFORM_COPYCONTENTS,  "1",
                         CURLFORM_END);
    }
  }


  ret = curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "apikey",
                     CURLFORM_COPYCONTENTS, file_scan->api_key,
                     CURLFORM_END);

  if (ret)
    VT_ERROR("Adding key\n");

  curl_easy_setopt(curl, CURLOPT_URL, VT_API_BASE_URL "file/rescan");

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
  curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost); // set form

  set_std_curl_data(file_scan, curl);


  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);
  DBG(1, "Perform done\n");
  /* Check for errors */
  if(res != CURLE_OK) {
    VT_ERROR("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    ret = res;
    goto cleanup;
  } else {
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_response_code);
    if (http_response_code != 200) {
      VT_ERROR("HTTP Response code: %ld\n", http_response_code);
      ret = http_response_code;
      goto cleanup;
    }
  }


  DBG(1, "Page:\n%s\n",file_scan->buffer);
  if (file_scan->response)
    VtResponse_put(&file_scan->response);

  file_scan->response = VtResponse_new();
  ret = VtResponse_fromJSONstr(file_scan->response, file_scan->buffer);
  if (ret) {
    VT_ERROR("Parsing JSON\n");
    goto cleanup;
  }

cleanup:
  /* always cleanup */
  curl_easy_cleanup(curl);

  if (formpost)
    curl_formfree(formpost);  // cleanup the formpost chain

  if (headerlist)
    curl_slist_free_all (headerlist); // free headers

  return ret;
}