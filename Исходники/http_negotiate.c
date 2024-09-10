/* returning zero (0) means success, everything else is treated as "failure"
   with no care exactly what the failure was */
int Curl_input_negotiate(struct connectdata *conn, bool proxy,
                         const char *header)
{
  struct SessionHandle *data = conn->data;
  struct negotiatedata *neg_ctx = proxy?&data->state.proxyneg:
    &data->state.negotiate;
  OM_uint32 major_status, minor_status, discard_st, min_stat;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  int ret;
  size_t len;
  size_t rawlen = 0;
  bool gss;
  const char* protocol;
  CURLcode error;

  while(*header && ISSPACE(*header))
    header++;
  if(checkprefix("GSS-Negotiate", header)) {
    protocol = "GSS-Negotiate";
    gss = TRUE;
  }
  else if(checkprefix("Negotiate", header)) {
    protocol = "Negotiate";
    gss = FALSE;
  }
  else
    return -1;

  if(neg_ctx->context) {
    if(neg_ctx->gss != gss) {
      return -1;
    }
  }
  else {
    neg_ctx->protocol = protocol;
    neg_ctx->gss = gss;
  }

  if(neg_ctx->context && neg_ctx->status == GSS_S_COMPLETE) {
    /* We finished successfully our part of authentication, but server
     * rejected it (since we're again here). Exit with an error since we
     * can't invent anything better */
    Curl_cleanup_negotiate(data);
    return -1;
  }

	if(neg_ctx->server_name == NULL &&
	  (ret = get_gss_name(conn, proxy, &neg_ctx->server_name)))
	return ret;
  	
  header += strlen(neg_ctx->protocol);
  while(*header && ISSPACE(*header))
    header++;

  len = strlen(header);
  if(len > 0) {
    error = Curl_base64_decode(header,
                               (unsigned char **)&input_token.value, &rawlen);
    if(error || rawlen == 0)
      return -1;
    input_token.length = rawlen;

    DEBUGASSERT(input_token.value != NULL);

#ifdef HAVE_SPNEGO /* Handle SPNEGO */
    if(checkprefix("Negotiate", header)) {
      unsigned char  *spnegoToken       = NULL;
      size_t          spnegoTokenLength = 0;
      gss_buffer_desc mechToken         = GSS_C_EMPTY_BUFFER;

      spnegoToken = malloc(input_token.length);
      if(spnegoToken == NULL) {
        Curl_safefree(input_token.value);
        return CURLE_OUT_OF_MEMORY;
      }
      memcpy(spnegoToken, input_token.value, input_token.length);
      spnegoTokenLength = input_token.length;

      if(!parseSpnegoTargetToken(spnegoToken,
                                 spnegoTokenLength,
                                 NULL,
                                 NULL,
                                 (unsigned char**)&mechToken.value,
                                 &mechToken.length,
                                 NULL,
                                 NULL)) {
        Curl_safefree(spnegoToken);
        infof(data, "Parse SPNEGO Target Token failed\n");
      }
      else if(!mechToken.value || !mechToken.length) {
        Curl_safefree(spnegoToken);
        if(mechToken.value)
          gss_release_buffer(&discard_st, &mechToken);
        infof(data, "Parse SPNEGO Target Token succeeded (NULL token)\n");
      }
      else {
        Curl_safefree(spnegoToken);
        Curl_safefree(input_token.value);
        input_token.value = malloc(mechToken.length);
        if(input_token.value == NULL) {
          gss_release_buffer(&discard_st, &mechToken);
          return CURLE_OUT_OF_MEMORY;
        }
        memcpy(input_token.value, mechToken.value, mechToken.length);
        input_token.length = mechToken.length;
        gss_release_buffer(&discard_st, &mechToken);
        infof(data, "Parse SPNEGO Target Token succeeded\n");
      }
    }
#endif
  }

  major_status = Curl_gss_init_sec_context(conn,
                                           &minor_status,
                                           &neg_ctx->context,
                                           neg_ctx->server_name,
                                           GSS_C_NO_CHANNEL_BINDINGS,
                                           &input_token,
                                           &output_token,
                                           NULL);
  gss_release_cred(&min_stat, &conn->data->curl_gss_creds);
  Curl_safefree(input_token.value);
  /*To remove the memory leak issue*/
  if(neg_ctx->server_name != GSS_C_NO_NAME)
    gss_release_name(&min_stat, &neg_ctx->server_name);

  neg_ctx->status = major_status;
  if(GSS_ERROR(major_status)) {
    if(output_token.value)
      gss_release_buffer(&discard_st, &output_token);
    log_gss_error(conn, minor_status, "KRB5_ERROR: gss_init_sec_context() failed: ");
	printf("\n KRB5_ERROR: gss_init_sec_context() failed error code : %d", minor_status);
    return -1;
  }

  if(!output_token.value || !output_token.length) {
    if(output_token.value)
      gss_release_buffer(&discard_st, &output_token);
    return -1;
  }

  neg_ctx->output_token = output_token;
  return 0;
}