CURLcode Curl_rtsp_parseheader(struct connectdata *conn,
                               char *header)
{
  struct Curl_easy *data = conn->data;
  long CSeq = 0;

  if(checkprefix("CSeq:", header)) {
    /* Store the received CSeq. Match is verified in rtsp_done */
    int nc = sscanf(&header[4], ": %ld", &CSeq);
    if(nc == 1) {
      struct RTSP *rtsp = data->req.protop;
      rtsp->CSeq_recv = CSeq; /* mark the request */
      data->state.rtsp_CSeq_recv = CSeq; /* update the handle */
    }
    else {
      failf(data, "Unable to read the CSeq header: [%s]", header);
      return CURLE_RTSP_CSEQ_ERROR;
    }
  }
  else if(checkprefix("Session:", header)) {
    char *start;

    /* Find the first non-space letter */
    start = header + 8;
    while(*start && ISSPACE(*start))
      start++;

    if(!*start) {
      failf(data, "Got a blank Session ID");
    }
    else if(data->set.str[STRING_RTSP_SESSION_ID]) {
      /* If the Session ID is set, then compare */
      if(strncmp(start, data->set.str[STRING_RTSP_SESSION_ID],
                 strlen(data->set.str[STRING_RTSP_SESSION_ID]))  != 0) {
        failf(data, "Got RTSP Session ID Line [%s], but wanted ID [%s]",
              start, data->set.str[STRING_RTSP_SESSION_ID]);
        return CURLE_RTSP_SESSION_ERROR;
      }
    }
    else {
      /* If the Session ID is not set, and we find it in a response, then set
       * it.
       *
       * Allow any non whitespace content, up to the field separator or end of
       * line. RFC 2326 isn't 100% clear on the session ID and for example
       * gstreamer does url-encoded session ID's not covered by the standard.
       */
      char *end = start;
      while(*end && *end != ';' && !ISSPACE(*end))
        end++;

      /* Copy the id substring into a new buffer */
      data->set.str[STRING_RTSP_SESSION_ID] = malloc(end - start + 1);
      if(data->set.str[STRING_RTSP_SESSION_ID] == NULL)
        return CURLE_OUT_OF_MEMORY;
      memcpy(data->set.str[STRING_RTSP_SESSION_ID], start, end - start);
      (data->set.str[STRING_RTSP_SESSION_ID])[end - start] = '\0';
    }
  }
  return CURLE_OK;
}